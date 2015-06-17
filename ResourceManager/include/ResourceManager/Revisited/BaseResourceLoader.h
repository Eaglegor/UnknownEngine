#pragma once

#include <ResourceManager/Revisited/IResourceLoader.h>
#include <ResourceManager/Revisited/ResourceTypeMetaInfo.h>

namespace UnknownEngine
{
	namespace Resources
	{
		template<typename T>
		class BaseResourceLoader : public IResourceLoader
		{
		public:
			virtual void* load() final
			{
				return loadImpl();
			}

			virtual void unload(void* data) final
			{
				unloadImpl(static_cast<T*>(data));
			}

			virtual void waitUntilFinished(){

			}

			virtual ResourceType getResourceType()
			{
				return ResourceTypeMetaInfo<T>::staticGetType();
			}

		private:
			virtual T* loadImpl() = 0;
			virtual void unloadImpl(T* data) = 0;
		};
	}
}
