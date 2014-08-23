#pragma once

#include <Listeners/BaseOgreComponentListener_fwd.h>
#include <Listeners/ThreadIndependentOgreComponentListenerBase.h>

#include <OgreRenderSubsystem_fwd.h>

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
	}
	namespace Graphics
	{

		class SingleThreadedOgreComponentListener : public ThreadIndependentOgreComponentListenerBase
		{
			public:
				SingleThreadedOgreComponentListener ( const std::string& object_name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ):
				ThreadIndependentOgreComponentListenerBase ( object_name, render_subsystem, engine_context )
				{}
				
				virtual ~SingleThreadedOgreComponentListener()
				{}

				virtual void processMessage ( const Core::PackedMessage& msg )
				{
						this->internalProcessMessage(msg);
				}
				
		};
	}
}
