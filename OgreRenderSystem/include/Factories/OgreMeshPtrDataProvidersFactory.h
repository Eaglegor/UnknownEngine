#pragma once

#include <ResourceManager/DataProviders/BaseDataProviderFactory.h>

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

		class OgreMeshPtrDataProvidersFactory : public Core::BaseDataProviderFactory
		{
		public:
			OgreMeshPtrDataProvidersFactory(Core::ILogger* logger, Core::EngineContext* engine_context, OgreRenderSubsystem* render_subsystem);
			virtual const char* getName() const override;
			
		private:
			Core::IDataProvider* createOgreMeshPtrFromMeshDataProvider ( const Core::DataProviderDesc& desc );
			
			Core::ILogger* logger;
			
			Core::EngineContext* engine_context;
			OgreRenderSubsystem* render_subsystem;
			
		};
	}
}