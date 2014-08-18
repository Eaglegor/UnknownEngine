#pragma once

#include <DataProvider/IDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class LogHelper;
	}

	namespace Graphics
	{

		class OgreRenderSubsystem;
		class OgreMeshPtrDataProvidersFactory : public Loader::IDataProviderFactory
		{
		public:
			OgreMeshPtrDataProvidersFactory(Core::LogHelper* log_helper, Core::EngineContext* engine_context, OgreRenderSubsystem* render_subsystem);
			virtual Loader::IDataProvider* createObject ( const Loader::DataProviderDesc& desc );
			virtual const std::string getName();
			virtual const std::unordered_set< Loader::DataProviderType >& getSupportedTypes();
			virtual const bool supportsType ( const Loader::DataProviderType& object_type );
			virtual void destroyObject ( Loader::IDataProvider* object );
			
		private:
			std::unordered_set<Loader::DataProviderType> supported_types;
			Core::LogHelper* log_helper;
			Core::EngineContext* engine_context;
			OgreRenderSubsystem* render_subsystem;

			Loader::IDataProvider* createOgreMeshPtrFromMeshDataProvider ( const Loader::DataProviderDesc &desc );
			void destroyOgreMeshPtrFromMeshDataProvider ( Loader::IDataProvider* data_provider );
		};
	}
}