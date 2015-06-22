#pragma once

#include <ResourceManager/ResourceLoaderOptions.h>
#include <ResourceManager/ResourceType.h>
#include <ResourceManager/ResourceLoaderType.h>

namespace UnknownEngine
{
	namespace Core
	{
		class LogHelper;
	}

	namespace Resources
	{
		class IResourceLoader
		{
		public:
			virtual ~IResourceLoader(){}

			virtual void load(void** out_data, size_t& out_data_size, Core::LogHelper &logger) = 0;
			virtual void unload(void** data, Core::LogHelper &logger) = 0;
			virtual void interrupt() = 0;

			virtual ResourceLoaderType getType() = 0;
			virtual ResourceType getResourceType() = 0;
		};
	}
}
