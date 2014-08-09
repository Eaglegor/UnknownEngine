#pragma once
#include <DataProvider/IDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Core
	{

		class LogHelper;
		class EngineContext;
	}

	namespace Loader
	{
		class AssimpMeshDataProvidersFactory : IDataProviderFactory
		{
		public:
			
			AssimpMeshDataProvidersFactory(Core::LogHelper* log_helper, Core::EngineContext* engine_context);
			
			virtual const std::string getName();
			virtual const std::unordered_set< DataProviderType >& getSupportedTypes();
			virtual void destroyObject ( IDataProvider* object );
			virtual IDataProvider* createObject ( const DataProviderDesc& desc );
			virtual const bool supportsType ( const DataProviderType& object_type );
			
		private:
			std::unordered_set< DataProviderType > supported_types;
			Core::LogHelper* log_helper;
			Core::EngineContext* engine_context;
		};
		
	}
}