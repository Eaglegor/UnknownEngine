#pragma once
#include <BaseComponentFactory.h>
#include <MessageSystem/BaseMessageListener.h>

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
		
		class OgreRenderSubsystem;
		
		class BaseOgreComponentFactory : public Core::BaseComponentFactory
		{
			public:

				BaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Utils::LogHelper* log_helper );
				~BaseOgreComponentFactory ();

				virtual void destroyObject ( Core::IComponent* object );
					
			protected:
				OgreRenderSubsystem* render_subsystem;
				Utils::LogHelper* log_helper;
				Core::EngineContext* engine_context;
		};
	}
}
