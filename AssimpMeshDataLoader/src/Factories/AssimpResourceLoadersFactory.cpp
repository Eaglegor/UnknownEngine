#include <stdafx.h>
#include <Factories/AssimpResourceLoadersFactory.h>
#include <ResourceLoaders/AssimpMeshDataLoader.h>
#include <Logging.h>

namespace UnknownEngine {
	namespace Resources
	{
		AssimpResourceLoadersFactory::AssimpResourceLoadersFactory()
		{
			SupportedTypeInfo supported_type;
			supported_type.type = "Assimp.MeshDataProvider";
			supported_type.creator = std::bind( &AssimpResourceLoadersFactory::createAssimpResourceLoader, this, std::placeholders::_1);
			registerSupportedType(supported_type);
		}

		Resources::IResourceLoader* AssimpResourceLoadersFactory::createAssimpResourceLoader(const Resources::ResourceLoaderOptions &options)
		{
			return new AssimpMeshDataLoader(options.createDescriptor<>);
		}
	}
}
