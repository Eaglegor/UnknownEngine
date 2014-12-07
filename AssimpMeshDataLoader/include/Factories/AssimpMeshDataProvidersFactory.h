#pragma once
#include <ResourceManager/DataProviders/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class ILogger;
	}

	namespace Loader
	{
		class AssimpMeshDataProvidersFactory : public Core::BaseDataProviderFactory
		{
		public:
			
			AssimpMeshDataProvidersFactory(Core::ILogger* logger, Core::EngineContext* engine_context);

			virtual const char* getName() const override;
			
		private:
			Core::IDataProvider* createAssimpMeshDataLoader( const Core::DataProviderDesc& desc );
			
			Core::ILogger* logger;
			Core::EngineContext* engine_context;
		};
		
	}
}