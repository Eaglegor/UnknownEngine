#pragma once
#include <DataProvider/LazyLoadDataProvider.h>
#include <Exception.h>
#include <ExportedMessages/LogMessage.h>
#include <memory>
#include <Descriptors/DataProviders/PxBoxGeometryDataProviderDesc.h>

namespace UnknownEngine
{
	namespace Core
	{

		class LogHelper;
		class EngineContext;
	}

	namespace Physics
	{

		static const Loader::DataProviderType PX_BOX_GEOMETRY_DATA_PROVIDER_TYPE_NAME = "Loader.PxGeometry.PxBoxGeometryDataProvider";
		
		class PxBoxGeometryDataProvider : public Loader::LazyLoadDataProvider
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(PxBoxGeometryLoadError);
			
			PxBoxGeometryDataProvider(const std::string& name, const PxBoxGeometryDataProviderDesc &desc, Core::EngineContext* engine_context);
			
			virtual const Loader::DataProviderType& getType();
			virtual void internalLoad ( Loader::ResourceContainer& out_container );
			
		private:
			PxBoxGeometryDataProviderDesc desc;
			std::unique_ptr<Core::LogHelper> log_helper;
			Core::EngineContext* engine_context;
		};
		
	}
}