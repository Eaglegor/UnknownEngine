#pragma once

#include <OgreRenderSubsystem_fwd.h>

#include <Objects/BaseComponent.h>
#include <MessageSystem/MessagingPoliciesManager.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class LogHelper;
	}

	namespace Graphics
	{

		class ThreadIndependentOgreComponentBase : public Core::BaseComponent
		{
			public:
				// Construction
				ThreadIndependentOgreComponentBase ( const std::string &name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );

				virtual ~ThreadIndependentOgreComponentBase();

				virtual void processMessages(){};
				
			protected:
				virtual void internalInit ( const Core::Entity* parent_entity ) = 0;
				virtual void internalShutdown( ) = 0;

				virtual void registerMessageProcessors ( Core::BaseMessageListener* message_listener ){}
				
				OgreRenderSubsystem* render_subsystem;
		};

	}
}
