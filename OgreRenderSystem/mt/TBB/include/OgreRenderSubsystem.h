#pragma once

#include <InlineSpecification.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/LogMessage.h>
#include <Descriptors/OgreRenderSubsystemDescriptor.h>
#include <functional>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include <ThreadIndependentOgreRenderSystemBase.h>
#include <Listeners/OgreUpdateFrameListener.h>
#include <LogHelper.h>

#include <OgreRenderSubsystem_fwd.h>
#include <OgreRenderFrameListener.h>


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

		class TBBOgreRenderSubsystem : public ThreadIndependentOgreRenderSystemBase
		{
			public:

				TBBOgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Core::LogHelper* log_helper, Core::EngineContext* engine_context ):
				ThreadIndependentOgreRenderSystemBase(desc, log_helper, engine_context)
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
						frame_listener.reset(new OgreRenderFrameListener());
						root->addFrameListener(frame_listener.get());
						rendering_thread.reset(new boost::thread( [this](){this->root->startRendering();}));
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
						frame_listener->stopRendering();
						frame_listener->waitUntilFinished();
					}
					
				}

				void addSynchronizeCallback ( const std::string &name, const std::function<void() > &callback )
				{
					frame_listener->addSynchronizeCallback(name, callback);
				}
				
				void removeSynchronizeCallback ( const std::string& name )
				{
					frame_listener->removeSynchronizeCallback(name);
				}
				
				void addInitCallback ( const std::function<void() > &callback )
				{
					frame_listener->addInitCallback(callback);
				}
				
				void addShutdownCallback ( const std::function<void() > &callback )
				{
					frame_listener->addShutdownCallback(callback);
				}
				
				void addRemoveCallback ( const std::function<void() > &callback )
				{
					frame_listener->addRemoveCallback(callback);
				}

				UNKNOWNENGINE_INLINE
				bool hasSeparateRenderThreadEnabled()
				{
					return desc.separate_rendering_thread;
				}

			private:
				std::unique_ptr<boost::thread> rendering_thread;
				std::unique_ptr<OgreRenderFrameListener> frame_listener;
				
		};

	} // namespace Graphics
} // namespace UnknownEngine
