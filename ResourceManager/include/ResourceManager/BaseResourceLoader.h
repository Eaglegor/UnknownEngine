#pragma once

#include <ResourceManager/IResourceLoader.h>
#include <ResourceManager/ResourceTypeMetaInfo.h>
#include <Concurrency/WaitingForEventWrapper.h>
#include <LogHelper.h>
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

			virtual void load(void** out_data, size_t &out_data_size, Core::LogHelper &logger) final
			{
				loadImpl(out_data, data_size, logger);
				if(out_data != nullptr && isInterrupted())
				{
					unload(out_data);
				}
				return data;
			}

			virtual void unload(void** data, Core::LogHelper &logger) final
			{
				unloadImpl(static_cast<T*>(data), logger);
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
			virtual void loadImpl(T** out_data, size_t &out_data_size, Core::LogHelper &logger) = 0;
			virtual void unloadImpl(T** data, Core::LogHelper &logger) = 0;

			volatile bool is_interrupted;
		};
	}
}
