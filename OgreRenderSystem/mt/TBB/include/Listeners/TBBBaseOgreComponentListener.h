#pragma once

#include <Listeners/BaseOgreComponentListener_fwd.h>
#include <Listeners/ThreadIndependentOgreComponentListenerBase.h>

#include <tbb/concurrent_queue.h>

#include <MessageBuffers/OnlyLastMessageBuffer.h>

#include <OgreRenderSubsystem.h>
#include <ExportedMessages/TransformChangedMessage.h>

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
				
				virtual void setTransformChangedMessageCallback( std::function<void (const Core::TransformChangedMessage& msg)> callback );
				
			private:

				tbb::concurrent_queue<Core::PackedMessage> messages_queue;
				
				std::unique_ptr< Utils::OnlyLastMessageBuffer<Core::TransformChangedMessage> > transform_changed_buffer;
				
				Core::MessageType transform_changed_message_type;
				
				void processAllQueuedMessages();

		};
	}
}
