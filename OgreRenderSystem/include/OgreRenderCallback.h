#pragma once
#include <OgreFrameListener.h>
#include <tbb/concurrent_unordered_map.h>
#include <functional>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreRenderCallback : public Ogre::FrameListener
		{
			private:
				typedef tbb::concurrent_unordered_map< std::string, std::function<void()> > ConcurrentMap;

			public:
				
				virtual bool frameStarted( const Ogre::FrameEvent& evt)
				{
					std::cout << "Starting frame" << std::endl;
					return true;
				}
				
				virtual bool frameEnded ( const Ogre::FrameEvent& evt )
				{
					std::cout << "Ending frame" << std::endl;
					ConcurrentMap::iterator init_iterator = init_callbacks.begin();
					while ( init_iterator != init_callbacks.end() )
					{
						init_iterator->second();
						init_iterator = init_callbacks.unsafe_erase ( init_iterator );
					}

					ConcurrentMap::iterator remove_iterator = remove_callbacks.begin();
					while ( remove_iterator != remove_callbacks.end() )
					{
						remove_iterator->second();
						remove_iterator = remove_callbacks.unsafe_erase ( remove_iterator );
					}

					ConcurrentMap::iterator synchronize_iterator = synchronize_callbacks.begin();
					while ( synchronize_iterator != synchronize_callbacks.end() )
					{
						synchronize_iterator->second();
						synchronize_iterator = synchronize_callbacks.unsafe_erase ( synchronize_iterator );
					}
					
					if(stopped) 
					{
						finished = true;
						wait_for_finish_var.notify_all();
					}
					
					std::cout << "Frame ended" << std::endl;
					
					return !stopped;
				};
				
				void addInitCallback ( const std::string &name, const std::function<void()> &callback )
				{
					init_callbacks.insert ( std::make_pair ( name, callback ) );
				}

				void addRemoveCallback ( const std::string &name, const std::function<void()> &callback )
				{
					remove_callbacks.insert ( std::make_pair ( name, callback ) );
				}

				void addSynchronizeCallback ( const std::string &name, const std::function<void()> &callback )
				{
					synchronize_callbacks.insert ( std::make_pair ( name, callback ) );
				}

				void removeSynchronizeCallback ( const std::string &name )
				{
					synchronize_callbacks.unsafe_erase ( name );
				}

				OgreRenderCallback():stopped(false),finished(false){}
				
				void stopRendering()
				{
					stopped = true;
				}
				
				void waitUntilFinished()
				{
					boost::unique_lock<boost::mutex> lock(loading_finished_mutex);
					while(!finished)
					{
						wait_for_finish_var.wait(lock);
					}
				}
				
			private:
				volatile bool stopped;
				volatile bool finished;
				boost::condition_variable wait_for_finish_var;
				boost::mutex loading_finished_mutex;
				
				/// Callbacks for components initialization which can be only done when rendering is inactive
				ConcurrentMap init_callbacks;

				/// Callbacks for components synchronization before rendering next frame (reacting on all incoming events)
				ConcurrentMap synchronize_callbacks;

				/// Callbacks for components removal
				ConcurrentMap remove_callbacks;
		};

	}
}
