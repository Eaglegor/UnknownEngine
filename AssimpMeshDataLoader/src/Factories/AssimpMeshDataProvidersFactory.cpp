#include <stdafx.h>
#include <Factories/AssimpMeshDataProvidersFactory.h>
#include <DataProviders/AssimpMeshDataProvider.h>
#include <Logging.h>
#include <ResourceManager/DataProviders/DataProviderDesc.h>
#include <Parsers/AssimpMeshDataProviderDescParser.h>
#include <DataProviders/AssimpMeshDataProviderDescriptorGetter.h>

namespace UnknownEngine {
	namespace Loader
	{
		
		static AssimpMeshDataProviderDescriptorGetter descriptor_getter;
		
		AssimpMeshDataProvidersFactory::AssimpMeshDataProvidersFactory ( Core::ILogger* logger, Core::EngineContext* engine_context ):
		logger(logger),
		engine_context(engine_context)
		{
			CreatableObjectDesc creatable_data_provider;
			creatable_data_provider.type = ASSIMP_MESH_DATA_PROVIDER_TYPE_NAME;
			creatable_data_provider.creator = std::bind( &AssimpMeshDataProvidersFactory::createAssimpMeshDataLoader, this, std::placeholders::_1);
			registerCreator(creatable_data_provider);
		}
		
		Core::IDataProvider* AssimpMeshDataProvidersFactory::createAssimpMeshDataLoader ( const Core::DataProviderDesc& desc )
		{
			Core::IDataProvider* result;

			LOG_INFO(logger, "Creating Assimp mesh data provider");
		
			result = new AssimpMeshDataProvider(desc.name, desc.descriptor.apply_visitor(descriptor_getter), engine_context);

			LOG_INFO(logger, "Data provider created");
			
			return result;
			
		}

		const char* AssimpMeshDataProvidersFactory::getName() const
		{
			return "Loader.MeshData.AssimpMeshDataProvidersFactory";
		}
		
	}
}