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
	}

	namespace Utils
	{
		class LogHelper;
	}
	
	namespace Graphics
	{

		class ThreadIndependentOgreComponentFactoryBase : public Core::BaseComponentFactory
		{
			public:

				virtual ~ThreadIndependentOgreComponentFactoryBase(){};
				ThreadIndependentOgreComponentFactoryBase ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Utils::LogHelper* log_helper ) :
					render_subsystem ( render_subsystem ),
					log_helper ( log_helper ),
					engine_context ( engine_context )
					{}

			protected:
			
				OgreRenderSubsystem* render_subsystem;
				Utils::LogHelper* log_helper;
				Core::EngineContext* engine_context;
		};
	}
}
