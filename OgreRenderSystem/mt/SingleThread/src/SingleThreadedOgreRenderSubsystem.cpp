#include <SingleThreadedOgreRenderSubsystem.h>
#include <LogHelper.h>
#include <Listeners/OgreUpdateFrameListener.h>

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

			LOG_INFO ( log_helper, "Registering update frame listener..." );
			update_frame_listener = new OgreUpdateFrameListener ( "Graphics.Ogre.Listeners.UpdateFrameListener", this );
			engine_context->getMessageDispatcher()->addListener ( Core::UpdateFrameMessage::getTypeName(), update_frame_listener );
		}
		
		void SingleThreadedOgreRenderSubsystem::stop()
		{
			LOG_INFO ( log_helper, "Unregistering update frame listener" );
			if ( update_frame_listener != nullptr )
			{
				engine_context->getMessageDispatcher()->removeListener ( update_frame_listener );
				delete update_frame_listener;
			}

			shutdownOgre();
		}
	}
}
