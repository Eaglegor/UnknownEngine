#pragma once

#include <ResourceManager/Revisited/ResourceLoaderType.h>
#include <ResourceManager/Revisited/IResourceLoader.h>

namespace UnknownEngine
{
	namespace Resources
	{
		class IResourceLoadersFactory
		{
		public:
			virtual ~IResourceLoadersFactory(){}

			virtual bool supportsType(const ResourceLoaderType& type) = 0;
			virtual IResourceLoader* createLoader(const ResourceLoaderType& type, const ResourceLoaderOptions &options);
			virtual void destroyLoader(IResourceLoader* loader);
		};
	}
}
