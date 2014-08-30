#pragma once
#include <BaseComponentFactory.h>
#include <MessageSystem/BaseMessageListener.h>
#include <OgreRenderSubsystem_fwd.h>
#include <Listeners/BaseMessageListenersFactory.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class LogHelper;
	}

	namespace Graphics
	{

		class ThreadIndependentOgreComponentFactoryBase : public Core::BaseComponentFactory
		{
			public:

				virtual ~ThreadIndependentOgreComponentFactoryBase(){};
				ThreadIndependentOgreComponentFactoryBase ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper ) :
					render_subsystem ( render_subsystem ),
					engine_context ( engine_context ),
					log_helper ( log_helper ) {}

			protected:
			
				Core::LogHelper* log_helper;
				OgreRenderSubsystem* render_subsystem;
				Core::EngineContext* engine_context;
		};
	}
}
