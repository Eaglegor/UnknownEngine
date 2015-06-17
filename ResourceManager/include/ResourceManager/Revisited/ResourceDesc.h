#pragma once

#include <ResourceManager/Revisited/ResourceType.h>
#include <ResourceManager/Revisited/ResourceLoaderType.h>
#include <ResourceManager/Revisited/ResourceLoaderOptions.h>
#include <ResourceManager/Revisited/PreloadPolicy.h>

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
