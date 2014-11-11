#include <stdafx.h>
#include <SingleThreadedOgreRenderSubsystem.h>
#include <LogHelper.h>
#include <Listeners/OgreUpdateFrameListener.h>
#include <MessageSystem/BaseMessageListener.h>
#include <ExportedMessages/RenderSystem/WindowResizedMessage.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		SingleThreadedOgreRenderSubsystem::SingleThreadedOgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Utils::LogHelper* log_helper, Core::EngineContext* engine_context ) :
			ThreadIndependentOgreRenderSystemBase ( desc, log_helper, engine_context )
		{}
		
		SingleThreadedOgreRenderSubsystem::~SingleThreadedOgreRenderSubsystem() {}
		
		void SingleThreadedOgreRenderSubsystem::start(const std::string &name, const Core::ReceivedMessageDescriptorsList& received_messages)
		{
			initOgre(name);

			listener.reset ( new Core::BaseMessageListener(name, engine_context) );
			listener->registerSupportedMessageTypes(received_messages);

			{
				typedef Core::UpdateFrameMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;

				listener->createMessageBuffer<MessageType, BufferType>(static_cast<ThreadIndependentOgreRenderSystemBase*>(this), &ThreadIndependentOgreRenderSystemBase::onFrameUpdated);
			}
			
			{
				typedef Graphics::WindowResizedMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;

				listener->createMessageBuffer<MessageType, BufferType>(static_cast<ThreadIndependentOgreRenderSystemBase*>(this), &SingleThreadedOgreRenderSubsystem::onWindowResized);
			}
			
			if(listener) listener->registerAtDispatcher();
		}
		
		void SingleThreadedOgreRenderSubsystem::stop()
		{
			if(listener) listener->unregisterAtDispatcher();

			shutdownOgre();
		}
	}
}
