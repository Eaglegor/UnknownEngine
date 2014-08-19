#pragma once
#include <Objects/Component.h>
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

		class OgreRenderSubsystem;
		
		class BaseOgreComponent : public Core::Component
		{
		public:
			// Construction
			BaseOgreComponent(const std::string &name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context);
			virtual ~BaseOgreComponent();
			
			// Lifecycle
			virtual void init ( const Core::Entity* parent_entity ) override;
			virtual void shutdown ( ) override;
			
		protected:
			virtual void internalInit( const Core::Entity* parent_entity ) = 0;
			virtual void internalShutdown( ) = 0;
			
			OgreRenderSubsystem* render_subsystem;
			Core::EngineContext* engine_context;
			Core::MessagingPoliciesManager messaging_policies_manager;
			std::unique_ptr<Core::LogHelper> log_helper;
		};
		
	}
}