#include <stdafx.h>
#include <Factories/AssimpResourceLoadersFactory.h>
#include <ResourceLoaders/AssimpMeshDataLoader.h>
#include <Descriptors/Schemas/Implementations/ResourceLoaders/Assimp/AssimpMeshDataLoaderDescSchema.h>
#include <Logging.h>

namespace UnknownEngine {
	namespace Resources
	{
		AssimpResourceLoadersFactory::AssimpResourceLoadersFactory()
		{
			SupportedTypeInfo supported_type;
			supported_type.type = ResourceLoaders::AssimpMeshDataLoader::staticGetType();
			supported_type.creator = std::bind(&AssimpResourceLoadersFactory::createAssimpResourceLoader, this, std::placeholders::_1);
			registerSupportedType(supported_type);
		}

		Resources::IResourceLoader* AssimpResourceLoadersFactory::createAssimpResourceLoader(const Resources::ResourceLoaderOptions &options)
		{
			return new ResourceLoaders::AssimpMeshDataLoader(options.createDescriptor(Utils::DescriptorSchema<AssimpMeshDataProviderDesc>()));
		}
	}
}
