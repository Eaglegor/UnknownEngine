#pragma once

#include <ResourceManager/ResourceLoaderOptions.h>
#include <ResourceManager/ResourceType.h>
#include <ResourceManager/ResourceLoaderType.h>

namespace UnknownEngine
{
	namespace Resources
	{
		class IResourceLoader
		{
		public:
			virtual ~IResourceLoader(){}

			virtual void* load() = 0;
			virtual void unload(void* data) = 0;
			virtual void interrupt() = 0;
			virtual size_t getDataSize() = 0;

			virtual ResourceLoaderType getType() = 0;
			virtual ResourceType getResourceType() = 0;
		};
	}
}
