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
		
		class OgreRenderableComponentsFactory: public BaseOgreComponentFactory
		{
			public:
				OgreRenderableComponentsFactory ( OgreRenderSubsystem* render_system, Core::EngineContext *engine_context, Core::ILogger* logger = nullptr );

				virtual const char* getName() const override;
		};

	} // namespace Graphics
} // namespace UnknownEngine
