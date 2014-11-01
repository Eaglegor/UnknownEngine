#pragma once

#include <Factories/BaseOgreComponentFactory.h>
#include <OgreRenderSubsystem_fwd.h>

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

		class OgreRenderableComponentsFactory: public BaseOgreComponentFactory
		{
			public:
				OgreRenderableComponentsFactory ( OgreRenderSubsystem* render_system, Core::EngineContext *engine_context, Utils::LogHelper* log_helper = nullptr );

				virtual const char* getName();
		};

	} // namespace Graphics
} // namespace UnknownEngine
