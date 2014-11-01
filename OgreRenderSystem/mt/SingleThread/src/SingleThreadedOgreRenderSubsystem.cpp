#include <SingleThreadedOgreRenderSubsystem.h>
#include <LogHelper.h>
#include <Listeners/OgreUpdateFrameListener.h>
#include <MessageSystem/BaseMessageListener.h>
#include <ExportedMessages/RenderSystem/WindowResizedMessage.h>
#include <Listeners/StandardMessageBuffersFactory.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		SingleThreadedOgreRenderSubsystem::SingleThreadedOgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Utils::LogHelper* log_helper, Core::EngineContext* engine_context ) :
			ThreadIndependentOgreRenderSystemBase ( desc, log_helper, engine_context )
		{}
		
		SingleThreadedOgreRenderSubsystem::~SingleThreadedOgreRenderSubsystem() {}
		
		void SingleThreadedOgreRenderSubsystem::start()
		{
			initOgre();

			listener.reset ( new Core::BaseMessageListener(std::string("Graphics.Ogre.Listeners.UpdateFrameListener"), engine_context) );

			listener->registerSupportedMessageType(Core::UpdateFrameMessage::getTypeName(), nullptr);
			listener->registerSupportedMessageType(Graphics::WindowResizedMessage::getTypeName(), nullptr);
			
			Utils::StandardMessageBuffersFactory<SingleThreadedOgreRenderSubsystem> factory(this);
			
			{
				typedef Core::UpdateFrameMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;

				BufferType buffer = factory.createBuffer<BufferType, MessageType>(&SingleThreadedOgreRenderSubsystem::onFrameUpdated);
				listener->registerMessageBuffer(buffer);
			}
			
			{
				typedef Graphics::WindowResizedMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;

				BufferType buffer = factory.createBuffer<BufferType, MessageType>(&SingleThreadedOgreRenderSubsystem::onWindowResized);
				listener->registerMessageBuffer(buffer);
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
