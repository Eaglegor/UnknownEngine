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
		
		class OgreCameraComponentsFactory: public BaseOgreComponentFactory
		{
			public:

				OgreCameraComponentsFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext *engine_context, Utils::LogHelper* log_helper = nullptr );

				virtual const char* getName() const override;
		};

	} // namespace Graphics
} // namespace UnknownEngine
