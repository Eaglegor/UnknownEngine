#pragma once
#include <BaseComponentFactory.h>
#include <MessageSystem/BaseMessageListener.h>

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
		
		class BaseOgreComponentFactory : public Core::BaseComponentFactory
		{
			public:

				BaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::ILogger* logger );
				~BaseOgreComponentFactory ();

				virtual void destroyObject ( Core::IComponent* object ) override;
					
			protected:
				OgreRenderSubsystem* render_subsystem;
				Core::ILogger* logger;
				Core::EngineContext* engine_context;
		};
	}
}
