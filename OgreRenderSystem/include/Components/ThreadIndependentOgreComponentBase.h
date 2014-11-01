#pragma once

#include <Objects/BaseComponent.h>
#include <OgreRenderSubsystem_fwd.h>

#include <MessageSystem/MessagingPoliciesManager.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class BaseMessageListener;
	}
	
	namespace Utils
	{
		class LogHelper;
	}

	namespace Graphics
	{

		class ThreadIndependentOgreComponentBase : public Core::BaseComponent
		{
			public:
				// Construction
				ThreadIndependentOgreComponentBase ( const std::string &name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );

				void setMessageListener(std::unique_ptr<Core::BaseMessageListener> listener);
				
				virtual ~ThreadIndependentOgreComponentBase();

			protected:
				virtual void internalInit ( const Core::Entity* parent_entity ) = 0;
				virtual void internalShutdown( ) = 0;

				virtual void initMessageListenerBuffers(bool can_be_multi_threaded){};
			
				std::unique_ptr<Core::BaseMessageListener> listener;
				
				OgreRenderSubsystem* render_subsystem;
				Core::EngineContext* engine_context;
				std::unique_ptr<Utils::LogHelper> log_helper;
				
		};

	}
}
