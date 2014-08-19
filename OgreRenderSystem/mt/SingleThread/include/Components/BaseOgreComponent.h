#pragma once
#include <Components/BaseOgreComponent_fwd.h>
#include <Objects/Component.h>
#include <MessageSystem/MessagingPoliciesManager.h>
#include <LogHelper.h>
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

		class SingleThreadedBaseOgreComponent : public Core::Component
		{
		public:
			// Construction
			SingleThreadedBaseOgreComponent(const std::string &name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context):
			Core::Component ( name ),
			render_subsystem(render_subsystem),
			engine_context(engine_context),
			messaging_policies_manager(engine_context)
			{}
			
			virtual ~SingleThreadedBaseOgreComponent()
			{}
			
			// Lifecycle
			virtual void init ( const Core::Entity* parent_entity ) override
			{
				internalInit( parent_entity );
			}
			
			virtual void shutdown ( ) override
			{
				internalShutdown();
			}
			
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