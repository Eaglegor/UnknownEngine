#pragma once

#include <OgreRenderSubsystem_fwd.h>

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

		class ThreadIndependentOgreComponentBase : public Core::IComponent
		{
			public:
				// Construction
				ThreadIndependentOgreComponentBase ( const std::string &name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );

				virtual ~ThreadIndependentOgreComponentBase();

			protected:
				virtual void internalInit ( const Core::Entity* parent_entity ) = 0;
				virtual void internalShutdown( ) = 0;

				OgreRenderSubsystem* render_subsystem;
				Core::EngineContext* engine_context;
				Core::MessagingPoliciesManager messaging_policies_manager;
				std::unique_ptr<Core::LogHelper> log_helper;
		};

	}
}
