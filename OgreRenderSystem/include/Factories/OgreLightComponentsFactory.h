#pragma once

#include <Factories/BaseOgreComponentFactory.h>

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
		
		class OgreLightComponentsFactory : public BaseOgreComponentFactory
		{
		public:
			OgreLightComponentsFactory(OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Utils::LogHelper* log_helper);
			virtual const char* getName() const override;
			
		};
	}
}