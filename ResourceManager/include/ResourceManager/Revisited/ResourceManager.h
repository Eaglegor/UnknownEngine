#pragma once

#include <ResourceManager/Revisited/ResourceDesc.h>
#include <ResourceManager/Revisited/ResourceGroup.h>
#include <ResourceManager/ThreadPool.h>
#include <unordered_set>
#include <unordered_map>

namespace UnknownEngine
{
	namespace Resources
	{
		class ResourceManager
		{
		public:
			ResourceManager();
			virtual ~ResourceManager();

			IResourceHandle* loadResource(const ResourceDesc &desc);
			IResourceHandle* findResource(const char* full_name);

			void addResourceLoadersFactory(IResourceLoadersFactory* factory);
			void removeResourceLoadersFactory(IResourceLoadersFactory* factory);

		private:
			Core::ThreadPool thread_pool;
			ResourceGroup main_resource_group;
			std::unordered_set<IResourceLoadersFactory*> resource_loaders_factories;
			std::unordered_map<ResourceLoaderType, IResourceLoadersFactory*> loader_type_factory_mapping;
		};
	}
}
