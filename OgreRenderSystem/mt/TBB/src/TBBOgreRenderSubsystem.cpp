#include <TBBOgreRenderSubsystem.h>
#include <LogHelper.h>
#include <Listeners/OgreUpdateFrameListener.h>
#include <MessageSystem/BaseMessageListener.h>
#include <Listeners/BaseMessageListenerBufferRegistrator.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <MessageBuffers/OnlyLastMessageBuffer.h>
#include <ExportedMessages/RenderSystem/WindowResizedMessage.h>
#include <OgreRoot.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		TBBOgreRenderSubsystem::TBBOgreRenderSubsystem ( const UnknownEngine::Graphics::OgreRenderSubsystemDescriptor& desc, UnknownEngine::Core::LogHelper* log_helper, UnknownEngine::Core::EngineContext* engine_context ) :
			ThreadIndependentOgreRenderSystemBase ( desc, log_helper, engine_context )
		{
			
		}
		
		TBBOgreRenderSubsystem::~TBBOgreRenderSubsystem() 
		{
			
		}
		
		void TBBOgreRenderSubsystem::start()
		{
			
			listener.reset ( new Core::BaseMessageListener(std::string("Graphics.Ogre.Listeners.UpdateFrameListener"), engine_context) );

			listener->registerSupportedMessageType(Core::UpdateFrameMessage::getTypeName(), nullptr);
			listener->registerSupportedMessageType(Graphics::WindowResizedMessage::getTypeName(), nullptr);
			
			Utils::BaseMessageListenerBufferRegistrator<TBBOgreRenderSubsystem> registrator(listener.get(), this);
			
			
			if ( !desc.separate_rendering_thread )
			{
				initOgre();
				
				registrator.registerStandardMessageBuffer<
				Core::UpdateFrameMessage,
				Utils::InstantForwardMessageBuffer<Core::UpdateFrameMessage>
				>(&TBBOgreRenderSubsystem::onFrameUpdated);
				
				registrator.registerStandardMessageBuffer<
				Graphics::WindowResizedMessage,
				Utils::InstantForwardMessageBuffer<Graphics::WindowResizedMessage>
				>(&TBBOgreRenderSubsystem::onWindowResized);
			}
			else
			{
				
				registrator.registerStandardMessageBuffer<
				Graphics::WindowResizedMessage,
				Utils::OnlyLastMessageBuffer<Graphics::WindowResizedMessage>
				>(&TBBOgreRenderSubsystem::onWindowResized);
				
				frame_listener.reset ( new OgreRenderFrameListener() );
				rendering_thread.reset ( new boost::thread ( [this]()
				{
					initOgre();
					addSynchronizeCallback("FlushMessageBuffers", [this](){listener->flushAllMessageBuffers();});
					root->addFrameListener ( frame_listener.get() );
					this->root->startRendering();
					root->removeFrameListener ( frame_listener.get() );
					removeSynchronizeCallback("FlushMessageBuffers");
					shutdownOgre();
					frame_listener->setFinished();
				} ) );
			}
			
			if(listener) listener->registerAtDispatcher();
		}
		
		void TBBOgreRenderSubsystem::stop()
		{
			if(listener) listener->unregisterAtDispatcher();

			if ( desc.separate_rendering_thread )
			{
				frame_listener->stopRendering();
				LOG_INFO( log_helper, "Waiting for OGRE shutdown");
				frame_listener->waitUntilFinished();
				LOG_INFO( log_helper, "Ogre shut down");
				frame_listener.reset();
			}
			else
			{
				shutdownOgre();
			}
		}
		
		void TBBOgreRenderSubsystem::addSynchronizeCallback ( const std::string& name, const std::function< void() >& callback )
		{
			if(frame_listener) frame_listener->addSynchronizeCallback ( name, callback );
		}
		
		void TBBOgreRenderSubsystem::removeSynchronizeCallback ( const std::string& name )
		{
			if(frame_listener) frame_listener->removeSynchronizeCallback ( name );
		}
		
		void TBBOgreRenderSubsystem::addInitCallback ( const std::function< void() >& callback )
		{
			if(frame_listener) frame_listener->addInitCallback ( callback );
		}
		
		void TBBOgreRenderSubsystem::addShutdownCallback ( const std::function< void() >& callback )
		{
			if(frame_listener) frame_listener->addShutdownCallback ( callback );
		}
		
		void TBBOgreRenderSubsystem::addRemoveCallback ( const std::function< void() >& callback )
		{
			if(frame_listener) frame_listener->addRemoveCallback ( callback );
		}
		
	}
}
