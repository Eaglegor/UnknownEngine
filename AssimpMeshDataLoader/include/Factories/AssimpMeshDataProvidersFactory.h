#pragma once
#include <DataProvider/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Core
	{

		class LogHelper;
		class EngineContext;
	}

	namespace Loader
	{
		class AssimpMeshDataProvidersFactory : public BaseDataProviderFactory
		{
		public:
			
			AssimpMeshDataProvidersFactory(Core::LogHelper* log_helper, Core::EngineContext* engine_context);

			virtual const char* getName();
			
		private:
			IDataProvider* createAssimpMeshDataLoader( const DataProviderDesc& desc );
			
			Core::LogHelper* log_helper;
			Core::EngineContext* engine_context;
		};
		
	}
}