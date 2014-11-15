#pragma once

#include <OgreFrameListener.h>

#ifdef OGRE_RS_WITH_TBB
	#include <Concurrency/DataStructures/TBBConcurrentQueue.h>
	#include <Concurrency/DataStructures/TBBConcurrentMap.h>
#else
	#include <Concurrency/DataStructures/LockingConcurrentQueue.h>
	#include <Concurrency/DataStructures/LockingConcurrentMap.h>
#endif


#include <Concurrency/WaitingForEventWrapper.h>
#include <Profiling/AverageFpsCounter.h>

#include <iostream>
#include <mutex>
#include <condition_variable>

namespace UnknownEngine
{

	namespace Graphics
	{
		class OgreRenderFrameListener : public Ogre::FrameListener
		{
		public:

		
#ifdef OGRE_RS_WITH_TBB
			typedef Utils::TBBConcurrentQueue< std::function<void()> > CallbacksQueue;
			typedef Utils::TBBConcurrentMap< std::string, std::function<void()> > CallbackMap;
#else
			typedef Utils::LockingConcurrentQueue< std::function<void()> > CallbacksQueue;
			typedef Utils::LockingConcurrentMap< std::string, std::function<void()> > CallbackMap;
#endif
			
			OgreRenderFrameListener();
			
			virtual bool frameStarted( const Ogre::FrameEvent& evt );

			void setFinished();

			void update();
			
			void stopRendering();

			void waitUntilFinished();

			void addSynchronizeCallback ( const std::string &name, const std::function<void() > &callback );

			void removeSynchronizeCallback ( const std::string& name );

			void addInitCallback ( const std::function<void() > &callback );

			void addShutdownCallback ( const std::function<void() > &callback );

			void addRemoveCallback ( const std::function<void() > &callback );

		private:
			
			Utils::WaitingForEventWrapper wait_for_finish;
			
			volatile bool stopped;
			std::mutex atomized_shutdown_and_remove_mutex;

			/// Callbacks for components initialization which can be only done when rendering is inactive
			CallbacksQueue init_callbacks;

			/// Callbacks for components synchronization before rendering next frame (reacting on all incoming events)
			CallbackMap synchronize_callbacks;

			/// Callbacks for shutdown components
			CallbacksQueue shutdown_callbacks;

			/// Callbacks for components removal
			CallbacksQueue remove_callbacks;
			
			Utils::AverageFpsCounter fps_counter;
		};

	}
}