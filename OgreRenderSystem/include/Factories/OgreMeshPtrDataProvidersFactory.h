#pragma once

#include <DataProvider/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class ILogger;
	}

	namespace Graphics
	{
		
		class OgreRenderSubsystem;

		class OgreMeshPtrDataProvidersFactory : public Loader::BaseDataProviderFactory
		{
		public:
			OgreMeshPtrDataProvidersFactory(Core::ILogger* logger, Core::EngineContext* engine_context, OgreRenderSubsystem* render_subsystem);
			virtual const char* getName() const override;
			
		private:
			Loader::IDataProvider* createOgreMeshPtrFromMeshDataProvider ( const Loader::DataProviderDesc& desc );
			
			Core::ILogger* logger;
			
			Core::EngineContext* engine_context;
			OgreRenderSubsystem* render_subsystem;
			
		};
	}
}