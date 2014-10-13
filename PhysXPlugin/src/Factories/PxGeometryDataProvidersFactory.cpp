#include <stdafx.h>

#include <Factories/PxGeometryDataProvidersFactory.h>

#include <DataProviders/PxBoxGeometryDataProvider.h>
#include <DataProviders/PxBoxGeometryDataProviderDescriptorGetter.h>
#include <DataProvider/DataProviderDesc.h>

namespace UnknownEngine {
	namespace Physics {

		static PxBoxGeometryDataProviderDescriptorGetter descriptor_getter;

		PxGeometryDataProvidersFactory::PxGeometryDataProvidersFactory(UnknownEngine::Core::LogHelper* log_helper, UnknownEngine::Core::EngineContext* engine_context)
			:log_helper(log_helper),
			engine_context(engine_context)
		{

			typedef PxGeometryDataProvidersFactory self_type;

			CreatableObjectDesc creatable_data_provider;
			creatable_data_provider.type = PX_BOX_GEOMETRY_DATA_PROVIDER_TYPE_NAME;
			creatable_data_provider.creator = std::bind(&self_type::createPxBoxGeometryDataProvider, this, std::placeholders::_1);
			registerCreator(creatable_data_provider);
		}

		const char* PxGeometryDataProvidersFactory::getName()
		{
			return "Physics.PhysXPlugin.PxGeometryDataProvidersFactory";
		}

		Loader::IDataProvider* PxGeometryDataProvidersFactory::createPxBoxGeometryDataProvider(const Loader::DataProviderDesc& desc)
		{
			PxBoxGeometryDataProviderDescriptorGetter descriptor_getter;
			return new PxBoxGeometryDataProvider(desc.name, desc.descriptor.apply_visitor(descriptor_getter), engine_context);
		}

	}
}