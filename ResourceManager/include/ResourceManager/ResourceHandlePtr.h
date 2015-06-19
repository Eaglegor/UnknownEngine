#pragma once

#include <ResourceManager/ResourceTypeMetaInfo.h>

namespace UnknownEngine
{
	namespace Resources
	{
		template<typename T>
		class ResourceHandlePtr
		{
		public:
			ResourceHandlePtr(IResourceHandle* handle):
			handle(nullptr)
			{
				if(handle)
				{
					if(handle->getType() == ResourceTypeMetaInfo<T>::staticGetType())
					{
						handle->reserve();
						this->handle = handle;
					}
				}
			}

			ResourceHandlePtr(ResourceHandlePtr<T> &handle_ptr)
			{
				this->handle = handle_ptr.handle;
				if(this->handle != nullptr)
				{
					handle->reserve();
				}
			}

			virtual ~ResourceHandlePtr()
			{
				if(handle) handle->release();
			}

			T* operator->()
			{
				return static_cast<T*>(handle->getData());
			}

			operator bool()
			{
				return handle != nullptr;
			}

			void lock()
			{
				handle->lock();
			}

			void unlock()
			{
				handle->unlock();
			}

		private:
			IResourceHandle* handle;
		};
	}
}
