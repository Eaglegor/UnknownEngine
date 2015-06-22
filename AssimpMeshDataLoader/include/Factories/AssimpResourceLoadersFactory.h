#pragma once
#include <ResourceManager/BaseResourceLoadersFactory.h>

namespace UnknownEngine
{
	namespace Resources
	{
		class AssimpResourceLoadersFactory : public Resources::BaseResourceLoadersFactory
		{
		public:
			AssimpResourceLoadersFactory();

		private:
			Resources::IResourceLoader* createAssimpResourceLoader(const Resources::ResourceLoaderOptions &options);
		};
		
	}
}
