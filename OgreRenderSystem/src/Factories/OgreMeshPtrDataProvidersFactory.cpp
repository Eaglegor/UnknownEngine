#include <stdafx.h>

#include <Factories/OgreMeshPtrDataProvidersFactory.h>

#include <DataProviders/OgreMeshPtrFromMeshDataProvider.h>
#include <Parsers/Descriptors/OgreMeshPtrFromMeshDataProviderDescriptorParser.h>
#include <DataProvider/DataProviderDesc.h>
#include <Factories/OgreGetDescriptorVisitor.h>

namespace UnknownEngine {
	namespace Graphics {
		
		static OgreGetDescriptorVisitor<OgreMeshPtrFromMeshDataProviderDescriptor, OgreMeshPtrFromMeshDataProviderDescriptorParser> descriptor_getter;
		
		OgreMeshPtrDataProvidersFactory::OgreMeshPtrDataProvidersFactory( Core::ILogger* logger, Core::EngineContext* engine_context, OgreRenderSubsystem* render_subsystem )
		:logger(logger),
		 engine_context(engine_context),
		 render_subsystem(render_subsystem)
		{
			
			typedef OgreMeshPtrDataProvidersFactory self_type;
			
			CreatableObjectDesc creatable_data_provider;
			creatable_data_provider.type = OGRE_MESH_PTR_FROM_MESH_DATA_PROVIDER_TYPE;
			creatable_data_provider.creator = std::bind(&self_type::createOgreMeshPtrFromMeshDataProvider, this, std::placeholders::_1);
			registerCreator(creatable_data_provider);
		}

		const char* OgreMeshPtrDataProvidersFactory::getName() const
		{
			return "Graphics.OgreRenderSystem.OgreMeshPtrDataProvidersFactory";
		}

		Loader::IDataProvider* OgreMeshPtrDataProvidersFactory::createOgreMeshPtrFromMeshDataProvider ( const Loader::DataProviderDesc& desc )
		{
			return new OgreMeshPtrFromMeshDataProvider(desc.name, desc.descriptor.apply_visitor(descriptor_getter), render_subsystem, engine_context);
		}
		
	}
}