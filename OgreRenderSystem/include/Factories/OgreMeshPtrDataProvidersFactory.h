#pragma once

#include <OgreRenderSubsystem_fwd.h>
#include <DataProvider/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class LogHelper;
	}

	namespace Graphics
	{

		class OgreMeshPtrDataProvidersFactory : public Loader::BaseDataProviderFactory
		{
		public:
			OgreMeshPtrDataProvidersFactory(Core::LogHelper* log_helper, Core::EngineContext* engine_context, OgreRenderSubsystem* render_subsystem);
			virtual const char* getName();
			
		private:
			Loader::IDataProvider* createOgreMeshPtrFromMeshDataProvider ( const Loader::DataProviderDesc& desc );
			
			Core::LogHelper* log_helper;
			
			Core::EngineContext* engine_context;
			OgreRenderSubsystem* render_subsystem;
			
		};
	}
}