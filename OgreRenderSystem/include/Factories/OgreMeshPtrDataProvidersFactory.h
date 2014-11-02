#pragma once

#include <OgreRenderSubsystem_fwd.h>
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
	
	namespace Graphics
	{

		class OgreMeshPtrDataProvidersFactory : public Loader::BaseDataProviderFactory
		{
		public:
			OgreMeshPtrDataProvidersFactory(Utils::LogHelper* log_helper, Core::EngineContext* engine_context, OgreRenderSubsystem* render_subsystem);
			virtual const char* getName();
			
		private:
			Loader::IDataProvider* createOgreMeshPtrFromMeshDataProvider ( const Loader::DataProviderDesc& desc );
			
			Utils::LogHelper* log_helper;
			
			Core::EngineContext* engine_context;
			OgreRenderSubsystem* render_subsystem;
			
		};
	}
}