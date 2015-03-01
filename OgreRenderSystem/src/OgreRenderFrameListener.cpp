#include <OgreRenderFrameListener.h>
#include <OgreRenderSubsystem.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreRenderFrameListener::OgreRenderFrameListener(OgreRenderSubsystem* render_subsystem) :
		render_subsystem(render_subsystem),
		stopped ( false )
		{}
		
		bool OgreRenderFrameListener::frameStarted ( const Ogre::FrameEvent& evt )
		{
			if(render_subsystem) render_subsystem->onUpdateFrame(evt.timeSinceLastFrame);

			return !stopped;
		}

		void OgreRenderFrameListener::waitUntilFinished()
		{
			wait_for_finish.wait();
		}
		
		void OgreRenderFrameListener::setFinished()
		{
			wait_for_finish.notify();
		}

		void OgreRenderFrameListener::stopRendering()
		{
			stopped = true;
		}

	}
}
