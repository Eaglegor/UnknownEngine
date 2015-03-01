#include <stdafx.h>

#include <Factories/OgreDataProvidersFactory.h>

#include <DataProviders/OgreMeshPtrFromMeshDataProvider.h>
#include <Parsers/Descriptors/OgreMeshPtrFromMeshDataProviderDescriptorParser.h>
#include <ResourceManager/DataProviders/DataProviderDesc.h>
#include <Factories/OgreGetDescriptorVisitor.h>
#include <OgreRenderSubsystem.h>

namespace UnknownEngine {
	namespace Graphics {
		
		static OgreGetDescriptorVisitor<OgreMeshPtrFromMeshDataProviderDescriptor, OgreMeshPtrFromMeshDataProviderDescriptorParser> descriptor_getter;
		
		OgreDataProvidersFactory::OgreDataProvidersFactory():
		render_subsystem(nullptr)
		{
			typedef OgreDataProvidersFactory self_type;
			
			CreatableObjectDesc creatable_data_provider;
			creatable_data_provider.type = OGRE_MESH_PTR_FROM_MESH_DATA_PROVIDER_TYPE;
			creatable_data_provider.creator = std::bind(&self_type::createOgreMeshPtrFromMeshDataProvider, this, std::placeholders::_1);
			registerCreator(creatable_data_provider);
		}

		void OgreDataProvidersFactory::setRenderSubsystem ( OgreRenderSubsystem* render_subsystem )
		{
			this->render_subsystem = render_subsystem;
		}
		
		const char* OgreDataProvidersFactory::getName() const
		{
			return "Ogre.DataProvidersFactory";
		}

		Core::IDataProvider* OgreDataProvidersFactory::createOgreMeshPtrFromMeshDataProvider ( const Core::DataProviderDesc& desc )
		{
			if(!render_subsystem) return nullptr;
			return new OgreMeshPtrFromMeshDataProvider(desc.name, desc.descriptor.apply_visitor(descriptor_getter), render_subsystem);
		}
		
	}
}