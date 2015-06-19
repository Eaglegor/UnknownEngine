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

			virtual void load(void** out_data, size_t &out_data_size) final
			{
				loadImpl(out_data, data_size);
				if(out_data != nullptr && isInterrupted())
				{
					unload(out_data);
				}
				return data;
			}

			virtual void unload(void** data) final
			{
				unloadImpl(static_cast<T*>(data));
				*data = nullptr;
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
			virtual void loadImpl(T** out_data, size_t &out_data_size) = 0;
			virtual void unloadImpl(T** data) = 0;

			volatile bool is_interrupted;
		};
	}
}
