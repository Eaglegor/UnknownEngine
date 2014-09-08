#pragma once

#include <OgreFrameListener.h>

#include <tbb/concurrent_queue.h>
#include <tbb/concurrent_unordered_map.h>

#include <iostream>
#include <mutex>
#include <condition_variable>

//#define AVERAGE_FPS_FRAMES_COUNT 10000

#ifdef AVERAGE_FPS_FRAMES_COUNT
	#include <chrono>
#endif

typedef tbb::concurrent_unordered_map< std::string, std::function<void() > > ConcurrentMap;
typedef tbb::concurrent_queue< std::function<void() > > ConcurrentQueue;

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreRenderFrameListener : public Ogre::FrameListener
		{
		public:

			OgreRenderFrameListener():
			stopped(false),
			finished(false)
#ifdef AVERAGE_FPS_FRAMES_COUNT
			,
			dur(0),
			counter(0)
#endif
			{}
			
			virtual bool frameStarted( const Ogre::FrameEvent& evt )
			{

#ifdef AVERAGE_FPS_FRAMES_COUNT
				std::chrono::steady_clock::time_point newTime = std::chrono::steady_clock::now();
				
				dur += newTime - old;
				++counter;
				old = newTime;
				
				if(counter == AVERAGE_FPS_FRAMES_COUNT)
				{
					float tm = dur.count() / static_cast<float>(counter);
					std::cout << "Average frame period: " << tm << " s" << std::endl;
					std::cout << "Average fps: " <<  1 / tm << std::endl;
					counter = 0;
					dur = dur.zero();
				}
#endif
				std::function<void()> callback;

				while ( init_callbacks.try_pop(callback) )
				{
					callback();
				}

				ConcurrentMap::iterator synchronize_iterator = synchronize_callbacks.begin();
				while ( synchronize_iterator != synchronize_callbacks.end() )
				{
					synchronize_iterator->second();
					++synchronize_iterator;
				}

				{
					std::unique_lock<std::mutex> guard(atomized_shutdown_and_remove_mutex);
					while ( shutdown_callbacks.try_pop(callback) )
					{
						callback();
					}

					while ( remove_callbacks.try_pop(callback) )
					{
						callback();
					}
				}
				
				return !stopped;
			}

			void setFinished()
			{
				std::unique_lock<std::mutex> lock(loading_finished_mutex);
				finished = true;
				wait_for_finish_var.notify_all();
			}

			void stopRendering()
			{
				stopped = true;
			}

			void waitUntilFinished()
			{
				std::unique_lock<std::mutex> lock(loading_finished_mutex);
				while(!finished)
				{
					wait_for_finish_var.wait(lock);
				}
			}

			void addSynchronizeCallback ( const std::string &name, const std::function<void() > &callback )
			{
				synchronize_callbacks.insert(std::make_pair(name, callback));
			}

			void removeSynchronizeCallback ( const std::string& name )
			{
				synchronize_callbacks.unsafe_erase(name);
			}

			void addInitCallback ( const std::function<void() > &callback )
			{
				init_callbacks.push(callback);
			}

			void addShutdownCallback ( const std::function<void() > &callback )
			{
				std::unique_lock<std::mutex> guard(atomized_shutdown_and_remove_mutex);
				shutdown_callbacks.push(callback);
			}

			void addRemoveCallback ( const std::function<void() > &callback )
			{
				std::unique_lock<std::mutex> guard(atomized_shutdown_and_remove_mutex);
				remove_callbacks.push(callback);
			}

		private:
			
			volatile bool stopped;
			volatile bool finished;
			std::condition_variable wait_for_finish_var;
			std::mutex loading_finished_mutex;
			std::mutex atomized_shutdown_and_remove_mutex;

			/// Callbacks for components initialization which can be only done when rendering is inactive
			ConcurrentQueue init_callbacks;

			/// Callbacks for components synchronization before rendering next frame (reacting on all incoming events)
			ConcurrentMap synchronize_callbacks;

			/// Callbacks for shutdown components
			ConcurrentQueue shutdown_callbacks;

			/// Callbacks for components removal
			ConcurrentQueue remove_callbacks;
			
#ifdef AVERAGE_FPS_FRAMES_COUNT
			size_t counter;
			std::chrono::duration<float> dur;
			std::chrono::steady_clock::time_point old;
#endif

		};

	}
}