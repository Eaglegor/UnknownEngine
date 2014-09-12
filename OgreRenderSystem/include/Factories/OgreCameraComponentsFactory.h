#pragma once

#include <Factories/BaseOgreComponentFactory.h>
#include <OgreRenderSubsystem_fwd.h>

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
		class LogHelper;
	}

	namespace Graphics
	{

		class OgreCameraComponentsFactory: public BaseOgreComponentFactory
		{
			public:

				OgreCameraComponentsFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext *engine_context, Core::LogHelper* log_helper = nullptr );

				virtual const char* getName();
		};

	} // namespace Graphics
} // namespace UnknownEngine