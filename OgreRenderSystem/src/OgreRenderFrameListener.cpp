#include <OgreRenderFrameListener.h>
#include <Profiling/SimpleFpsPrinter.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreRenderFrameListener::OgreRenderFrameListener() :
		stopped ( false ),
		fps_counter(10000, Utils::SimpleFpsPrinter("RT AVG FPS: "))
		{}
		
		bool OgreRenderFrameListener::frameStarted ( const Ogre::FrameEvent& evt )
		{
			update();

			return !stopped;
		}
		
		void OgreRenderFrameListener::update()
		{
			//fps_counter.nextFrame();
			std::function<void() > callback;

			{
				std::unique_lock<std::mutex> guard ( atomized_init_and_synchronize_mutex );
				while ( init_callbacks.try_pop ( callback ) )
				{
					callback();
				}

				synchronize_callbacks.for_each([&](std::pair<const std::string, std::function<void () > >& val){ val.second(); } );
			}

			{
				std::unique_lock<std::mutex> guard ( atomized_shutdown_and_remove_mutex );
				while ( shutdown_callbacks.try_pop ( callback ) )
				{
					callback();
				}

				while ( remove_callbacks.try_pop ( callback ) )
				{
					callback();
				}
			}
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
		
		void OgreRenderFrameListener::addSynchronizeCallback ( const std::string& name, const std::function< void() >& callback )
		{
			++scount;
			std::unique_lock<std::mutex> guard ( atomized_init_and_synchronize_mutex );
			synchronize_callbacks.insert ( std::make_pair ( name, callback ) );
		}
		void OgreRenderFrameListener::removeSynchronizeCallback ( const std::string& name )
		{
			std::unique_lock<std::mutex> guard ( atomized_init_and_synchronize_mutex );
			synchronize_callbacks.erase ( name );
			--scount;
		}
		void OgreRenderFrameListener::addInitCallback ( const std::function< void() >& callback )
		{
			std::unique_lock<std::mutex> guard ( atomized_init_and_synchronize_mutex );
			init_callbacks.push ( callback );
		}
		void OgreRenderFrameListener::addShutdownCallback ( const std::function< void() >& callback )
		{
			std::unique_lock<std::mutex> guard ( atomized_shutdown_and_remove_mutex );
			shutdown_callbacks.push ( callback );
		}
		void OgreRenderFrameListener::addRemoveCallback ( const std::function< void() >& callback )
		{
			std::unique_lock<std::mutex> guard ( atomized_shutdown_and_remove_mutex );
			remove_callbacks.push ( callback );
		}

	}
}
