#pragma once
#include <DataProvider/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
	}

	namespace Utils
	{
		class LogHelper;
	}
	
	namespace Loader
	{
		class AssimpMeshDataProvidersFactory : public BaseDataProviderFactory
		{
		public:
			
			AssimpMeshDataProvidersFactory(Utils::LogHelper* log_helper, Core::EngineContext* engine_context);

			virtual const char* getName();
			
		private:
			IDataProvider* createAssimpMeshDataLoader( const DataProviderDesc& desc );
			
			Utils::LogHelper* log_helper;
			Core::EngineContext* engine_context;
		};
		
	}
}