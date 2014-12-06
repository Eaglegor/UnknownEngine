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
		
		class OgreCameraComponentsFactory: public BaseOgreComponentFactory
		{
			public:

				OgreCameraComponentsFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext *engine_context, Core::ILogger* logger = nullptr );

				virtual const char* getName() const override;
		};

	} // namespace Graphics
} // namespace UnknownEngine
