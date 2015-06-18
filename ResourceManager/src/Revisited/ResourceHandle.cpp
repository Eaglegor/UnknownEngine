#include <ResourceManager/Revisited/ResourceHandle.h>

namespace UnknownEngine
{
	namespace Resources
	{

		ResourceHandle::ResourceHandle(const char* name, const char* group_name, IResourceLoader* loader, ObsoleteResourceHandleListener *obsolete_handle_listener):
		name(name),
		group_name(group_name),
		loader(loader),
		loaders_factory(nullptr),
		obsolete_handle_listener(obsolete_handle_listener),
		resource_data(nullptr),
		ref_counter(1),
		data_size(0)
		{
		}

		ResourceHandle::~ResourceHandle()
		{
			if(resource_data != nullptr)
			{
				loader->unload(resource_data);
				resource_data = nullptr;
			}
			else
			{
				if(loader->isLoading())
				{
					loader->interrupt();
					loader->waitUntilFinished();
				}
			}
		}

		void ResourceHandle::startLoading()
		{
			if(!loader->isLoading())
			{
				resource_data = loader->load();
			}
		}

		void ResourceHandle::reserve()
		{
			++ref_counter;
		}

		void ResourceHandle::release()
		{
			if(--ref_counter <= 1)
			{
				obsolete_handle_listener->onHandleObsolete(this);
			}
		}

		ResourceType ResourceHandle::getResourceType()
		{
			return loader->getResourceType();
		}

		void* ResourceHandle::getData()
		{
			if(resource_data == nullptr)
			{
				if(!loader->isLoading())
				{
					resource_data = loader->load();
				}
				loader->waitUntilFinished();
			}
			return resource_data;
		}

		size_t ResourceHandle::getDataSize()
		{
			return loader->getDataSize();
		}

		virtual const char * ResourceHandle::getName()
		{
			return name.c_str();
		}

		virtual const char * ResourceHandle::getResourceGroupName()
		{
			return group_name.c_str();
		}

		void ResourceHandle::setLoadersFactory(IResourceLoadersFactory* loaders_factory)
		{
			this->loaders_factory = loaders_factory;
		}

		IResourceLoadersFactory* ResourceHandle::getLoadersFactory()
		{
			return loaders_factory;
		}

	}
}

