#pragma once

#include <Listeners/BaseOgreComponentListener_fwd.h>
#include <Listeners/ThreadIndependentOgreComponentListenerBase.h>

#include <tbb/concurrent_queue.h>

#include <OgreRenderSubsystem.h>

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
	}
	namespace Graphics
	{

		class TBBOgreComponentListener : public ThreadIndependentOgreComponentListenerBase
		{
			public:

				TBBOgreComponentListener ( const std::string& object_name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );
				
				virtual ~TBBOgreComponentListener();

				virtual void processMessage ( const Core::PackedMessage& msg );
				
			private:

				
				tbb::concurrent_queue<Core::PackedMessage> messages_queue;
				
				void processAllQueuedMessages();

		};
	}
}
