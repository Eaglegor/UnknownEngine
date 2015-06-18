#pragma once

#include <ResourceManager/Revisited/IResourceLoader.h>
#include <ResourceManager/Revisited/IResourceHandle.h>
#include <ResourceManager/Revisited/ObsoleteResourceHandleListener.h>
#include <ResourceManager/Revisited/IResourceLoadersFactory.h>

namespace UnknownEngine
{
	namespace Resources
	{
		class ResourceHandle : public IResourceHandle
		{
		public:
			ResourceHandle(const char* name, const char* group_name, IResourceLoader* loader, ObsoleteResourceHandleListener* obsolete_handle_listener);
			virtual ~ResourceHandle();

			virtual void startLoading();

			virtual void reserve() override;
			virtual void release() override;
			virtual ResourceType getResourceType() override;
			virtual void* getData() override;

			virtual const char *getName();
			virtual const char *getResourceGroupName();

			size_t getDataSize() override;
			IResourceLoader* getLoader();

			void setLoadersFactory(IResourceLoadersFactory* loaders_factory);
			IResourceLoadersFactory* getLoadersFactory();

		private:
			typedef int RefCounter;

			RefCounter ref_counter;
			size_t data_size;

			std::string name;
			std::string group_name;

			ObsoleteResourceHandleListener* obsolete_handle_listener;

			IResourceLoadersFactory* loaders_factory;
			IResourceLoader* loader;
			void* resource_data;

		};
	}
}
