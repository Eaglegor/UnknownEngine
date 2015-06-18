#pragma once

#include <ResourceManager/Revisited/IResourceLoader.h>
#include <ResourceManager/Revisited/ResourceTypeMetaInfo.h>
#include <Concurrency/WaitingForEventWrapper.h>

namespace UnknownEngine
{
	namespace Resources
	{
		template<typename T>
		class BaseResourceLoader : public IResourceLoader
		{
		public:
			BaseResourceLoader():
			is_loading(false),
			is_interrupted(false)
			{}

			virtual void* load() final
			{
				is_loading = true;
				void* data = loadImpl();
				is_loading = false;
				if(data != nullptr && isInterrupted())
				{
					unload(data);
				}
				else
				{
					wait_for_loading.notify();
				}
				return data;
			}

			virtual void unload(void* data) final
			{
				unloadImpl(static_cast<T*>(data));
			}

			virtual ResourceType getResourceType()
			{
				return ResourceTypeMetaInfo<T>::staticGetType();
			}

			virtual bool isLoading(){
				return is_loading;
			}

			virtual void interrupt() final override
			{
				is_interrupted = true;
			}

			virtual void waitUntilFinished()
			{
				wait_for_loading.wait();
			}

		protected:
			bool isInterrupted()
			{
				return is_interrupted;
			}

		private:
			Utils::WaitingForEventWrapper wait_for_loading;

			virtual T* loadImpl() = 0;
			virtual void unloadImpl(T* data) = 0;

			bool is_loading;
			bool is_interrupted;
		};
	}
}
