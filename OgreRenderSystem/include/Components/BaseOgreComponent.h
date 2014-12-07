#pragma once

#include <ComponentSystem/BaseComponent.h>

#include <MessageSystem/MessagingPoliciesManager.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class BaseMessageListener;
		class ILogger;
	}

	namespace Graphics
	{

		class OgreRenderSubsystem;
		
		class BaseOgreComponent : public Core::BaseComponent
		{
			public:
				BaseOgreComponent ( const std::string &name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );

				void setMessageListener(std::unique_ptr<Core::BaseMessageListener> listener);
				
				virtual ~BaseOgreComponent();

				virtual void init ( const Core::IEntity* parent_entity ) override;

				virtual void shutdown ( ) override;
				
			protected:
				volatile bool shutdown_initialized;
				
				virtual void internalInit ( const Core::IEntity* parent_entity ) = 0;
				virtual void internalShutdown( ) = 0;

				virtual void initMessageListenerBuffers(bool can_be_multi_threaded){};
			
				std::unique_ptr<Core::BaseMessageListener> listener;
				
				OgreRenderSubsystem* render_subsystem;
				Core::EngineContext* engine_context;
				Core::ILogger* logger;
				
		};

	}
}
