#include <ResourceManager/ResourceManager.h>
#include <ResourceManager/ResourceHandle.h>
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string/find.hpp>

namespace UnknownEngine
{
	namespace Core
	{
		template<>
		ResourceManager* Singleton<ResourceManager>::instance = nullptr;

		ResourceManager::ResourceManager(size_t loader_threads_count):
		thread_pool(loader_threads_count),
		obsolete_handle_listener(std::bind(&ResourceManager::onHandleObsolete, this, std::placeholders::_1))
		{
		}

		ResourceManager::~ResourceManager()
		{

		}

		IResourceHandle* ResourceManager::loadResource(const ResourceDesc& desc)
		{
			ResourceLoaderType& loader_type = desc.resource_loader_type;
			IResourceLoadersFactory* loaders_factory = nullptr;
			auto iter = loader_type_factory_mapping.find(loader_type);
			if(iter != loader_type_factory_mapping.end())
			{
				loaders_factory = iter->second;
			}
			else
			{
				auto set_iter = std::find_if(
							resource_loaders_factories.begin(),
							resource_loaders_factories.end(),
							[&loader_type](IResourceLoaderFactory* factory)
							{
								return factory->supportsType(loader_type);
							}
				);
				if(set_iter != resource_loaders_factories.end())
				{
					loaders_factory = *iter;
				}
			}

			if(loaders_factory == nullptr)
			{
				// REPORT ERROR!
				return nullptr;
			}

			IResourceLoader* loader = loaders_factory->createLoader(loader_type, desc.resource_loader_options);

			if(loader == nullptr)
			{
				// Something went wrong. Report error
				return nullptr;
			}

			ResourceHandle* handle = new ResourceHandle(desc.name.c_str(), desc.resource_group.c_str(), loader, &obsolete_handle_listener);

			handle->setLoadersFactory(loaders_factory);

			ResourceGroup* group = findResourceGroup(desc.resource_group.c_str(), true);

			if(group == nullptr)
			{
				// Something went totally wrong. Reporting error.
				delete handle;
				loaders_factory->destroyLoader(loader);
				return nullptr;
			}

			group->addResourceHandle(desc.name.c_str(), handle);

			if(desc.preload_policy == PreloadPolicy::FORCE_PRELOAD || desc.preload_policy == PreloadPolicy::AUTO)
			{
				thread_pool.pushTask(std::bind(&ResourceHandle::startLoading, handle));
			}

			return handle;
		}

		IResourceHandle* ResourceManager::findResource(const char* full_name)
		{
			std::string fullname = full_name;
			size_t lastdot = fullname.find_last_of('.');
			if(lastdot == fullname.npos)
			{
				return main_resource_group.findResourceHandle(full_name);
			}
			else
			{
				std::string group_name = fullname.substr(0, lastdot);
				std::string resource_name = fullname.substr(lastdot + 1, fullname.size() - lastdot);
				ResourceGroup* group = findResourceGroup(group_name.c_str());
				if(group == nullptr) return nullptr;
				return group->findResourceHandle(resource_name.c_str());
			}
		}

		void ResourceManager::addResourceLoadersFactory(
				IResourceLoadersFactory* factory)
		{
			loader_type_factory_mapping.clear();
			resource_loaders_factories.emplace(factory);
		}

		void ResourceManager::removeResourceLoadersFactory(
				IResourceLoadersFactory* factory)
		{
			resource_loaders_factories.erase(factory);
		}

		ResourceGroup* ResourceManager::findResourceGroup(const char* full_name, bool create_if_not_exists)
		{
			typedef boost::algorithm::split_iterator<std::string::iterator> string_split_iterator;
			ResourceGroup* current_resource_group = &main_resource_group;
			for(string_split_iterator iter = make_split_iterator(full_name, boost::algorithm::first_finder(".", boost::algorithm::is_equal()));
				iter != string_split_iterator(); ++iter)
			{
				auto sequence = boost::copy_range<std::string>(*iter).c_str();
				ResourceGroup *new_group = current_resource_group->getNestedResourceGroup( sequence.c_str() );
				if(new_group == nullptr){
					if(create_if_not_exists)
					{
						new_group = current_resource_group->createNestedResourceGroup( sequence.c_str() );
					}
					else
					{
						return nullptr;
					}
				}
				current_resource_group = new_group;
			}
			return current_resource_group;
		}

		void ResourceManager::onHandleObsolete(ResourceHandle* handle){
			ResourceGroup* group = findResourceGroup(handle->getResourceGroupName());

			assert(group->findResourceHandle(handle->getName() == handle));

			group->removeResourceHandle(handle->getName());

			IResourceLoadersFactory* factory = handle->getLoadersFactory();
			IResourceLoader* loader = handle->getLoader();

			delete handle;

			factory->destroyLoader(loader);
		}

	}
}
