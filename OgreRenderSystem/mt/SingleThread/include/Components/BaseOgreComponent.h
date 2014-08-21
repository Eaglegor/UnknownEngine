#pragma once
#include <Components/BaseOgreComponent_fwd.h>
#include <Components/ThreadIndependentOgreComponentBase.h>
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

		class SingleThreadedBaseOgreComponent : public ThreadIndependentOgreComponentBase
		{
		public:
			SingleThreadedBaseOgreComponent(const std::string &name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context):
			ThreadIndependentOgreComponentBase ( name, render_subsystem, engine_context )
			{}
			
			virtual ~SingleThreadedBaseOgreComponent()
			{}
			
			virtual void init ( const Core::Entity* parent_entity ) override
			{
				internalInit( parent_entity );
			}
			
			virtual void shutdown ( ) override
			{
				internalShutdown();
			}

		};
		
	}
}