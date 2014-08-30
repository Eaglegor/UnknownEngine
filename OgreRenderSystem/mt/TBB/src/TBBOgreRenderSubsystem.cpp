#include <TBBOgreRenderSubsystem.h>
#include <LogHelper.h>
#include <Listeners/OgreUpdateFrameListener.h>
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
			if ( !desc.separate_rendering_thread )
			{
				LOG_INFO ( log_helper, "Registering update frame listener..." );
				update_frame_listener = new OgreUpdateFrameListener ( "Graphics.Ogre.Listeners.UpdateFrameListener", this );
				engine_context->getMessageDispatcher()->addListener ( Core::UpdateFrameMessage::getTypeName(), update_frame_listener );
				
				initOgre();
			}
			else
			{
				frame_listener.reset ( new OgreRenderFrameListener() );
				rendering_thread.reset ( new boost::thread ( [this]()
				{
					initOgre();
					root->addFrameListener ( frame_listener.get() );
					this->root->startRendering();
					root->removeFrameListener ( frame_listener.get() );
					shutdownOgre();
					frame_listener->setFinished();
				} ) );
			}
		}
		
		void TBBOgreRenderSubsystem::stop()
		{
			if ( update_frame_listener != nullptr )
			{
				LOG_INFO ( log_helper, "Unregistering update frame listener" );
				engine_context->getMessageDispatcher()->removeListener ( update_frame_listener );
				delete update_frame_listener;
			}

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
