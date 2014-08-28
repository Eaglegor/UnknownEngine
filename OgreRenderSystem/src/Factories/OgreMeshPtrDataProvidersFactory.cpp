#include <stdafx.h>

#include <Factories/OgreMeshPtrDataProvidersFactory.h>

#include <DataProviders/OgreMeshPtrFromMeshDataProvider.h>
#include <Parsers/Descriptors/OgreMeshPtrFromMeshDataProviderDescriptorParser.h>
#include <DataProvider/DataProviderDesc.h>

namespace UnknownEngine {
	namespace Graphics {
		
		OgreMeshPtrDataProvidersFactory::OgreMeshPtrDataProvidersFactory( UnknownEngine::Core::LogHelper* log_helper, UnknownEngine::Core::EngineContext* engine_context, UnknownEngine::Graphics::OgreRenderSubsystem* render_subsystem )
		:log_helper(log_helper),
		 engine_context(engine_context),
		 render_subsystem(render_subsystem)
		{
			supported_types.insert(OGRE_MESH_PTR_FROM_MESH_DATA_PROVIDER_TYPE);
		}
		
		Loader::IDataProvider* OgreMeshPtrDataProvidersFactory::createObject ( const Loader::DataProviderDesc& desc )
		{
			if(desc.type == OGRE_MESH_PTR_FROM_MESH_DATA_PROVIDER_TYPE)
			{
				return createOgreMeshPtrFromMeshDataProvider(desc);
			}
			return nullptr;
		}

		void OgreMeshPtrDataProvidersFactory::destroyObject ( Loader::IDataProvider* object )
		{
			if(object->getType() == OGRE_MESH_PTR_FROM_MESH_DATA_PROVIDER_TYPE)
			{
				destroyOgreMeshPtrFromMeshDataProvider(object);
			}
		}

		const char* OgreMeshPtrDataProvidersFactory::getName()
		{
			return "Graphics.OgreRenderSystem.OgreMeshPtrDataProvidersFactory";
		}

		const std::unordered_set< Loader::DataProviderType >& OgreMeshPtrDataProvidersFactory::getSupportedTypes()
		{
			return supported_types;
		}

		const bool OgreMeshPtrDataProvidersFactory::supportsType ( const Loader::DataProviderType& object_type )
		{
			return supported_types.find(object_type) != supported_types.end();
		}
		
		Loader::IDataProvider* OgreMeshPtrDataProvidersFactory::createOgreMeshPtrFromMeshDataProvider ( const Loader::DataProviderDesc& desc )
		{
			if(!desc.descriptor.isEmpty())
			{
				return new OgreMeshPtrFromMeshDataProvider(desc.name, desc.descriptor.get<OgreMeshPtrFromMeshDataProviderDescriptor>(), render_subsystem, engine_context);
			}
			else
			{
				return new OgreMeshPtrFromMeshDataProvider(desc.name, OgreMeshPtrFromMeshDataProviderDescriptorParser::parse(desc.creation_options), render_subsystem, engine_context);
			}
		}

		void OgreMeshPtrDataProvidersFactory::destroyOgreMeshPtrFromMeshDataProvider ( Loader::IDataProvider* data_provider )
		{
			delete data_provider;
		}
		
	}
}