#pragma once

#include <Factories/BaseOgreComponentFactory.h>

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
		
		class OgreLightComponentsFactory : public BaseOgreComponentFactory
		{
		public:
			OgreLightComponentsFactory(OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::ILogger* logger);
			virtual const char* getName() const override;
			
		};
	}
}