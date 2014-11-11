#include <stdafx.h>
#include <TBBOgreRenderSubsystem.h>
#include <LogHelper.h>
#include <Listeners/OgreUpdateFrameListener.h>
#include <MessageSystem/BaseMessageListener.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <MessageBuffers/OnlyLastMessageBuffer.h>
#include <ExportedMessages/RenderSystem/WindowResizedMessage.h>
#include <OgreRoot.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		TBBOgreRenderSubsystem::TBBOgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Utils::LogHelper* log_helper, Core::EngineContext* engine_context ) :
			ThreadIndependentOgreRenderSystemBase ( desc, log_helper, engine_context )
		{
			
		}
		
		TBBOgreRenderSubsystem::~TBBOgreRenderSubsystem() 
		{
			
		}
		
		void TBBOgreRenderSubsystem::start(const std::string& name, const Core::ReceivedMessageDescriptorsList& received_messages)
		{
			
			listener.reset ( new Core::BaseMessageListener(name, engine_context) );
			listener->initMessageSlots(received_messages);
			
			if ( !desc.separate_rendering_thread )
			{
				initOgre(name);
				
				{
					typedef Core::UpdateFrameMessage MessageType;
					typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
					
					listener->createMessageBuffer<MessageType, BufferType>(static_cast<ThreadIndependentOgreRenderSystemBase*>(this), &ThreadIndependentOgreRenderSystemBase::onFrameUpdated);
				}
				
				{
					typedef Graphics::WindowResizedMessage MessageType;
					typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
					
					listener->createMessageBuffer<MessageType, BufferType>(static_cast<ThreadIndependentOgreRenderSystemBase*>(this), &ThreadIndependentOgreRenderSystemBase::onWindowResized);
				}
				
			}
			else
			{
				
				{
					typedef Graphics::WindowResizedMessage MessageType;
					typedef Utils::OnlyLastMessageBuffer<MessageType> BufferType;
					
					listener->createMessageBuffer<MessageType, BufferType>(static_cast<ThreadIndependentOgreRenderSystemBase*>(this), &ThreadIndependentOgreRenderSystemBase::onWindowResized);
				}
				
				frame_listener.reset ( new OgreRenderFrameListener() );
				rendering_thread.reset ( new boost::thread ( [this, name]()
				{
					initOgre(name);
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
