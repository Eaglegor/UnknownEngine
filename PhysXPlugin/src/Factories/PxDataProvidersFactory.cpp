#include <stdafx.h>
#include <Factories/PxDataProvidersFactory.h>
#include <DataProviders/PxBoxShapeDataProvider.h>
#include <Parsers/PxBoxShapeDataProviderDescriptorGetter.h>
#include <DataProviders/PxMaterialDataProvider.h>
#include <Parsers/PxMaterialDataProviderDescriptorGetter.h>
#include <ResourceManager/DataProviders/DataProviderDesc.h>

namespace UnknownEngine
{
	namespace Physics
	{
		
		static PxBoxShapeDataProviderDescriptorGetter px_box_shape_descriptor_getter;
		static PxMaterialDataProviderDescriptorGetter px_material_descriptor_getter;

		PxDataProvidersFactory::PxDataProvidersFactory ():
		physx_subsystem(nullptr)
		{
			CreatableObjectDesc creatable_data_provider;
			creatable_data_provider.type = PX_BOX_SHAPE_DATA_PROVIDER_TYPE;
			creatable_data_provider.creator = std::bind(&PxDataProvidersFactory::createPxBoxShapeDataProvider, this, std::placeholders::_1);
			registerCreator(creatable_data_provider);
			
			creatable_data_provider.type = PX_MATERIAL_DATA_PROVIDER_TYPE;
			creatable_data_provider.creator = std::bind(&PxDataProvidersFactory::createPxMaterialDataProvider, this, std::placeholders::_1);
			registerCreator(creatable_data_provider);
		}

		void PxDataProvidersFactory::setPhysXSubsystem ( PhysXSubsystem* physx_subsystem )
		{
			this->physx_subsystem = physx_subsystem;
		}
		
		Core::IDataProvider* PxDataProvidersFactory::createPxBoxShapeDataProvider ( const Core::DataProviderDesc& desc )
		{
			if(!physx_subsystem) return nullptr;
			PxBoxShapeDataProvider* result;
			result = new PxBoxShapeDataProvider(desc.name, desc.descriptor.apply_visitor(px_box_shape_descriptor_getter), physx_subsystem);
			return result;
		}
		
		Core::IDataProvider* PxDataProvidersFactory::createPxMaterialDataProvider ( const Core::DataProviderDesc& desc )
		{
			if(!physx_subsystem) return nullptr;
			PxMaterialDataProvider* result;
			result = new PxMaterialDataProvider(desc.name, desc.descriptor.apply_visitor(px_material_descriptor_getter), physx_subsystem);
			return result;
		}
		
	}
}