#include <Factories/AssimpMeshDataProvidersFactory.h>
#include <DataProviders/AssimpMeshDataProvider.h>
#include <LogHelper.h>
#include <DataProvider/DataProviderDesc.h>
#include <Parsers/AssimpMeshDataProviderDescParser.h>

namespace UnknownEngine {
	namespace Loader
	{
		
		AssimpMeshDataProvidersFactory::AssimpMeshDataProvidersFactory ( UnknownEngine::Core::LogHelper* log_helper, UnknownEngine::Core::EngineContext* engine_context ):
		log_helper(log_helper),
		engine_context(engine_context)
		{
			supported_types.insert(ASSIMP_MESH_DATA_PROVIDER_TYPE_NAME);
		}
		
		IDataProvider* AssimpMeshDataProvidersFactory::createObject ( const DataProviderDesc& desc )
		{
			IDataProvider* result;

			LOG_INFO(log_helper, "Creating Assimp mesh data provider");
		
			if(!desc.descriptor.isEmpty())
			{
				LOG_INFO(log_helper, "Predefined descriptor found");
				result = new AssimpMeshDataProvider(desc.name, desc.descriptor.get<AssimpMeshDataProvider::Descriptor>(), engine_context);
			}
			else
			{
				LOG_WARNING(log_helper, "Predefined descriptor not found. String parser will be used instead");
				result = new AssimpMeshDataProvider(desc.name, AssimpMeshDataProviderDescParser::parse(desc.creation_options), engine_context);
			}

			LOG_INFO(log_helper, "Data provider created");
			
			return result;
			
		}

		void AssimpMeshDataProvidersFactory::destroyObject ( IDataProvider* object )
		{
			delete object;
		}

		const char* AssimpMeshDataProvidersFactory::getName()
		{
			return "Loader.MeshData.AssimpMeshDataProvidersFactory";
		}

		const std::unordered_set< DataProviderType >& AssimpMeshDataProvidersFactory::getSupportedTypes()
		{
			return supported_types;
		}

		const bool AssimpMeshDataProvidersFactory::supportsType ( const DataProviderType& object_type )
		{
			return supported_types.find(object_type)!=supported_types.end();
		}

	}
}