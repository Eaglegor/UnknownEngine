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
			
			typedef OgreMeshPtrDataProvidersFactory self_type;
			
			CreatableObjectDesc creatable_data_provider;
			creatable_data_provider.type = OGRE_MESH_PTR_FROM_MESH_DATA_PROVIDER_TYPE;
			creatable_data_provider.creator = std::bind(&self_type::createOgreMeshPtrFromMeshDataProvider, this, std::placeholders::_1);
			registerCreator(creatable_data_provider);
		}

		const char* OgreMeshPtrDataProvidersFactory::getName()
		{
			return "Graphics.OgreRenderSystem.OgreMeshPtrDataProvidersFactory";
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
		
	}
}