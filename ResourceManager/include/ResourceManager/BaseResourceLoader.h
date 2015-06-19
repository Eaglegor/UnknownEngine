#pragma once

#include <ResourceManager/IResourceLoader.h>
#include <ResourceManager/ResourceTypeMetaInfo.h>
#include <Concurrency/WaitingForEventWrapper.h>
#include <Spinlock.h>
#include <mutex>

namespace UnknownEngine
{
	namespace Resources
	{
		template<typename T>
		class BaseResourceLoader : public IResourceLoader
		{
		public:
			BaseResourceLoader():
			is_interrupted(false)
			{}

			virtual void* load() final
			{
				void* data = loadImpl();
				if(data != nullptr && isInterrupted())
				{
					unload(data);
					data = nullptr;
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

			virtual void interrupt() final override
			{
				is_interrupted = true;
			}

		protected:
			bool isInterrupted()
			{
				return is_interrupted;
			}

		private:
			virtual T* loadImpl() = 0;
			virtual void unloadImpl(T* data) = 0;

			volatile bool is_interrupted;
		};
	}
}
