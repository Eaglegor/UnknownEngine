#include <Factories/PxMaterialDataProvidersFactory.h>
#include <DataProviders/PxMaterialDataProvider.h>
#include <Parsers/PxMaterialDataProviderDescriptorGetter.h>

namespace UnknownEngine
{
	namespace Physics
	{
		
		static PxMaterialDataProviderDescriptorGetter px_material_descriptor_getter;
		
		const char* PxMaterialDataProvidersFactory::getName()
		{
			return "Physics.PhysXPlugin.PxMaterialDataProvidersFactory";
		}

		PxMaterialDataProvidersFactory::PxMaterialDataProvidersFactory ( PhysXSubsystem* physx_subsystem ):
		physx_subsystem(physx_subsystem)
		{
			CreatableObjectDesc creatable_data_provider;
			creatable_data_provider.type = PX_MATERIAL_DATA_PROVIDER_TYPE;
			creatable_data_provider.creator = std::bind(&PxMaterialDataProvidersFactory::createPxMaterialDataProvider, this, std::placeholders::_1);
			registerCreator(creatable_data_provider);
		}

		Loader::IDataProvider* PxMaterialDataProvidersFactory::createPxMaterialDataProvider ( const Loader::DataProviderDesc& desc )
		{
			PxMaterialDataProvider* result;
			result = new PxMaterialDataProvider(desc.name, desc.descriptor.apply_visitor(px_material_descriptor_getter), physx_subsystem);
			return result;
		}
		
	}
}