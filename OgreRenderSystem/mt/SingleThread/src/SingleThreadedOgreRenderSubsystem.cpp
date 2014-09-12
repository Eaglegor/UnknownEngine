#include <SingleThreadedOgreRenderSubsystem.h>
#include <LogHelper.h>
#include <Listeners/OgreUpdateFrameListener.h>
#include <MessageSystem/BaseMessageListener.h>
#include <ExportedMessages/RenderSystem/WindowResizedMessage.h>
#include <Listeners/BaseMessageListenerBufferRegistrator.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		SingleThreadedOgreRenderSubsystem::SingleThreadedOgreRenderSubsystem ( const UnknownEngine::Graphics::OgreRenderSubsystemDescriptor& desc, UnknownEngine::Core::LogHelper* log_helper, UnknownEngine::Core::EngineContext* engine_context ) :
			ThreadIndependentOgreRenderSystemBase ( desc, log_helper, engine_context )
		{}
		
		SingleThreadedOgreRenderSubsystem::~SingleThreadedOgreRenderSubsystem() {}
		
		void SingleThreadedOgreRenderSubsystem::start()
		{
			initOgre();

			listener.reset ( new Core::BaseMessageListener(std::string("Graphics.Ogre.Listeners.UpdateFrameListener"), engine_context) );

			listener->registerSupportedMessageType(Core::UpdateFrameMessage::getTypeName(), nullptr);
			listener->registerSupportedMessageType(Graphics::WindowResizedMessage::getTypeName(), nullptr);
			
			Utils::BaseMessageListenerBufferRegistrator<SingleThreadedOgreRenderSubsystem> registrator(listener.get(), this);
			
			registrator.registerStandardMessageBuffer<
			Core::UpdateFrameMessage,
			Utils::InstantForwardMessageBuffer<Core::UpdateFrameMessage>
			>(&SingleThreadedOgreRenderSubsystem::onFrameUpdated);
			
			registrator.registerStandardMessageBuffer<
			Graphics::WindowResizedMessage,
			Utils::InstantForwardMessageBuffer<Graphics::WindowResizedMessage>
			>(&SingleThreadedOgreRenderSubsystem::onWindowResized);
			
			if(listener) listener->registerAtDispatcher();
		}
		
		void SingleThreadedOgreRenderSubsystem::stop()
		{
			if(listener) listener->unregisterAtDispatcher();

			shutdownOgre();
		}
	}
}
