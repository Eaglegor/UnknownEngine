#include <stdafx.h>
#include <Factories/PxShapeDataProvidersFactory.h>
#include <DataProviders/PxBoxShapeDataProvider.h>
#include <Parsers/PxBoxShapeDataProviderDescriptorGetter.h>
#include <ResourceManager/DataProviders/DataProviderDesc.h>

namespace UnknownEngine
{
	namespace Physics
	{
		
		static PxBoxShapeDataProviderDescriptorGetter px_box_shape_descriptor_getter;
		
		const char* PxShapeDataProvidersFactory::getName() const
		{
			return "Physics.PhysXPlugin.PxShapeDataProvidersFactory";
		}

		PxShapeDataProvidersFactory::PxShapeDataProvidersFactory ( PhysXSubsystem* physx_subsystem ):
		physx_subsystem(physx_subsystem)
		{
			CreatableObjectDesc creatable_data_provider;
			creatable_data_provider.type = PX_BOX_SHAPE_DATA_PROVIDER_TYPE;
			creatable_data_provider.creator = std::bind(&PxShapeDataProvidersFactory::createPxBoxShapeDataProvider, this, std::placeholders::_1);
			registerCreator(creatable_data_provider);
		}

		Core::IDataProvider* PxShapeDataProvidersFactory::createPxBoxShapeDataProvider ( const Core::DataProviderDesc& desc )
		{
			PxBoxShapeDataProvider* result;
			result = new PxBoxShapeDataProvider(desc.name, desc.descriptor.apply_visitor(px_box_shape_descriptor_getter), physx_subsystem);
			return result;
		}
		
	}
}