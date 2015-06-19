#pragma once

#include <ResourceManager/IResourceLoader.h>
#include <ResourceManager/IResourceHandle.h>
#include <ResourceManager/ObsoleteResourceHandleListener.h>
#include <ResourceManager/IResourceLoadersFactory.h>
#include <Concurrency/WaitingForEventWrapper.h>
#include <mutex>

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
			typedef std::mutex LockPrimitive;

			Utils::WaitingForEventWrapper wait_for_loading;

			typedef int RefCounter;

			LockPrimitive lock;

			volatile bool is_loading;

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
