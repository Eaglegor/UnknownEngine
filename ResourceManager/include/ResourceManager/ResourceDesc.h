#pragma once

#include <ResourceManager/ResourceType.h>
#include <ResourceManager/ResourceLoaderType.h>
#include <ResourceManager/ResourceLoaderOptions.h>
#include <ResourceManager/PreloadPolicy.h>

namespace UnknownEngine
{
	namespace Resources
	{
		struct ResourceDesc
		{
			std::string name;
			std::string resource_group;
			PreloadPolicy preload_policy;
			ResourceType resource_type;
			ResourceLoaderType resource_loader_type;
			ResourceLoaderOptions resource_loader_options;
		};
	}
}
