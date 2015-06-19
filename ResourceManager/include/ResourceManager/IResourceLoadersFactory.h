#pragma once

#include <ResourceManager/ResourceLoaderType.h>
#include <ResourceManager/IResourceLoader.h>

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
