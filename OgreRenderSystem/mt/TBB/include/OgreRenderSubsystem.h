#pragma once

#include <InlineSpecification.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/LogMessage.h>
#include <Descriptors/OgreRenderSubsystemDescriptor.h>
#include <functional>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/lock_types.hpp>
#include <boost/thread/pthread/mutex.hpp>
#include <boost/thread/pthread/condition_variable_fwd.hpp>
#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include <BaseOgreRenderSubsystem.h>
#include <Listeners/OgreUpdateFrameListener.h>
#include <LogHelper.h>

#include <OgreRenderSubsystem_fwd.h>

#include <tbb/concurrent_queue.h>
#include <tbb/concurrent_unordered_map.h>

typedef tbb::concurrent_unordered_map< std::string, std::function<void() > > ConcurrentMap;
typedef tbb::concurrent_queue< std::function<void() > > ConcurrentQueue;

namespace Ogre
{
	class SceneManager;
	class RenderWindow;
	class LogManager;
}

namespace UnknownEngine
{

	namespace Core
	{
		class LogHelper;
		class EngineContext;
	}

	namespace Graphics
	{

		class OgreRenderCallback;

		class OgreUpdateFrameListener;

		class TBBOgreRenderSubsystem : public BaseOgreRenderSubsystem
		{
			public:

				TBBOgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Core::LogHelper* log_helper, Core::EngineContext* engine_context ):
				BaseOgreRenderSubsystem(desc, log_helper, engine_context)
				{
				}
				
				virtual ~TBBOgreRenderSubsystem(){};

				virtual void start()
				{
					if ( !desc.separate_rendering_thread )
					{
						LOG_INFO ( log_helper, "Registering update frame listener..." );
						update_frame_listener = new OgreUpdateFrameListener ( "Graphics.Ogre.Listeners.UpdateFrameListener", this );
						engine_context->getMessageDispatcher()->addListener ( Core::UpdateFrameMessage::getTypeName(), update_frame_listener );
					}
					else
					{
						rendering_thread.reset ( new boost::thread ( boost::bind(&TBBOgreRenderSubsystem::internalLoop, this) ) );
					}
				}

				virtual void stop()
				{
					if ( update_frame_listener != nullptr )
					{
						LOG_INFO ( log_helper, "Unregistering update frame listener" );
						engine_context->getMessageDispatcher()->removeListener ( update_frame_listener );
						delete update_frame_listener;
					}
					
					if(desc.separate_rendering_thread)
					{
						stopRendering();
						waitUntilFinished();
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
					shutdown_callbacks.push(callback);
				}
				
				void addRemoveCallback ( const std::function<void() > &callback )
				{
					remove_callbacks.push(callback);
				}

				UNKNOWNENGINE_INLINE
				bool hasSeparateRenderThreadEnabled()
				{
					return desc.separate_rendering_thread;
				}

				bool prepareToRender()
				{
					/*std::cout << "Ending frame" << std::endl;
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
					
					return !stopped;*/
				}
				
				void internalLoop()
				{
					prepareToRender();
					Ogre::WindowEventUtilities::messagePump();
					root->renderOneFrame();
				}
				
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
				ConcurrentQueue init_callbacks;

				/// Callbacks for components synchronization before rendering next frame (reacting on all incoming events)
				ConcurrentMap synchronize_callbacks;

				/// Callbacks for shutdown components
				ConcurrentQueue shutdown_callbacks;

				/// Callbacks for components removal
				ConcurrentQueue remove_callbacks;

				std::unique_ptr<boost::thread> rendering_thread;
		};

	} // namespace Graphics
} // namespace UnknownEngine
