#pragma once

#include <OgreFrameListener.h>

#include <Concurrency/WaitingForEventWrapper.h>

namespace UnknownEngine
{

	namespace Graphics
	{

		class OgreRenderSubsystem;
		class OgreRenderFrameListener : public Ogre::FrameListener
		{
		public:

			OgreRenderFrameListener(OgreRenderSubsystem* render_subsystem);
			
			virtual bool frameStarted( const Ogre::FrameEvent& evt ) override;

			void setFinished();

			void stopRendering();

			void waitUntilFinished();
			
		private:
			OgreRenderSubsystem* render_subsystem;
			
			Utils::WaitingForEventWrapper wait_for_finish;
			
			volatile bool stopped;
		};

	}
}