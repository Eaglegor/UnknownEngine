#pragma once

#include <DataProvider/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class LogHelper;
	}

	namespace Physics
	{

		class PxGeometryDataProvidersFactory : public Loader::BaseDataProviderFactory
		{
		public:
			PxGeometryDataProvidersFactory(Core::LogHelper* log_helper, Core::EngineContext* engine_context);
			virtual const char* getName();
			
		private:
			Loader::IDataProvider* createPxBoxGeometryDataProvider ( const Loader::DataProviderDesc& desc );
			
			Core::LogHelper* log_helper;
			
			Core::EngineContext* engine_context;
			
		};
	}
}