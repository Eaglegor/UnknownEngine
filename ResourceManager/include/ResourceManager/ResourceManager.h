#pragma once

#include <ResourceManager/ResourceDesc.h>
#include <ResourceManager/ResourceGroup.h>
#include <ResourceManager/IResourceLoadersFactory.h>
#include <ResourceManager/ObsoleteResourceHandleListener.h>
#include <ResourceManager/ThreadPool.h>
#include <Singleton.h>
#include <unordered_set>
#include <unordered_map>

namespace UnknownEngine
{
	namespace Core
	{
		class ResourceManager : public Core::Singleton<ResourceManager>
		{
		public:
			ResourceManager(size_t loader_threads_count);
			virtual ~ResourceManager();

			IResourceHandle* loadResource(const ResourceDesc &desc);
			IResourceHandle* findResource(const char* full_name);

			void addResourceLoadersFactory(IResourceLoadersFactory* factory);
			void removeResourceLoadersFactory(IResourceLoadersFactory* factory);

		private:
			ResourceGroup* findResourceGroup(const char* full_name, bool create_if_not_exists = false);

			void onHandleObsolete(ResourceHandle* handle);

			Core::ThreadPool thread_pool;
			ResourceGroup main_resource_group;
			ObsoleteResourceHandleListener obsolete_handle_listener;
			std::unordered_set<IResourceLoadersFactory*> resource_loaders_factories;
			std::unordered_map<ResourceLoaderType, IResourceLoadersFactory*> loader_type_factory_mapping;
		};

#ifdef _MSC_VER
#ifndef ResourceManager_EXPORTS
		extern template class RESOURCEMANAGER_EXPORT Singleton<ResourceManager>;
#else
		template class RESOURCEMANAGER_EXPORT Singleton<ResourceManager>;
#endif
#endif

	}
}
