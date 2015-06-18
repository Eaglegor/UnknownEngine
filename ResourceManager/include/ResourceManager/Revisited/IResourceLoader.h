#pragma once

#include <ResourceManager/Revisited/ResourceLoaderOptions.h>
#include <ResourceManager/Revisited/ResourceType.h>
#include <ResourceManager/Revisited/ResourceLoaderType.h>

namespace UnknownEngine
{
	namespace Resources
	{
		class IResourceLoader
		{
		public:
			virtual ~IResourceLoader(){}

			virtual bool isLoading() = 0;
			virtual void* load() = 0;
			virtual void waitUntilFinished() = 0;
			virtual void unload(void* data) = 0;
			virtual void interrupt() = 0;
			virtual size_t getDataSize() = 0;

			virtual ResourceLoaderType getType() = 0;
			virtual ResourceType getResourceType() = 0;
		};
	}
}
