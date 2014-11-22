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
	
	namespace Graphics
	{
		
		class OgreRenderSubsystem;

		class OgreMeshPtrDataProvidersFactory : public Loader::BaseDataProviderFactory
		{
		public:
			OgreMeshPtrDataProvidersFactory(Utils::LogHelper* log_helper, Core::EngineContext* engine_context, OgreRenderSubsystem* render_subsystem);
			virtual const char* getName() const override;
			
		private:
			Loader::IDataProvider* createOgreMeshPtrFromMeshDataProvider ( const Loader::DataProviderDesc& desc );
			
			Utils::LogHelper* log_helper;
			
			Core::EngineContext* engine_context;
			OgreRenderSubsystem* render_subsystem;
			
		};
	}
}