#pragma once
#include <DataProvider/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class ILogger;
	}

	namespace Loader
	{
		class AssimpMeshDataProvidersFactory : public BaseDataProviderFactory
		{
		public:
			
			AssimpMeshDataProvidersFactory(Core::ILogger* logger, Core::EngineContext* engine_context);

			virtual const char* getName() const override;
			
		private:
			IDataProvider* createAssimpMeshDataLoader( const DataProviderDesc& desc );
			
			Core::ILogger* logger;
			Core::EngineContext* engine_context;
		};
		
	}
}