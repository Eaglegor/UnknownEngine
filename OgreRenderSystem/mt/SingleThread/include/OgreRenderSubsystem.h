#pragma once

#include <OgreRenderSubsystem_fwd.h>

#include <InlineSpecification.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/LogMessage.h>
#include <Descriptors/OgreRenderSubsystemDescriptor.h>
#include <functional>

#include <BaseOgreRenderSubsystem.h>
#include <Listeners/OgreUpdateFrameListener.h>
#include <LogHelper.h>

namespace boost
{
	class thread;
}

namespace Ogre
{
	class Root;
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

		class SingleThreadedOgreRenderSubsystem : public BaseOgreRenderSubsystem
		{
			public:

				SingleThreadedOgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Core::LogHelper* log_helper, Core::EngineContext* engine_context ):
				BaseOgreRenderSubsystem(desc, log_helper, engine_context)
				{};
				
				virtual ~SingleThreadedOgreRenderSubsystem(){};
				
				virtual void start()
				{
					LOG_INFO ( log_helper, "Registering update frame listener..." );
					update_frame_listener = new OgreUpdateFrameListener ( "Graphics.Ogre.Listeners.UpdateFrameListener", this );
					engine_context->getMessageDispatcher()->addListener ( Core::UpdateFrameMessage::getTypeName(), update_frame_listener );
				}
				
				virtual void stop()
				{
					LOG_INFO ( log_helper, "Unregistering update frame listener" );
					if(update_frame_listener != nullptr)
					{
						engine_context->getMessageDispatcher()->removeListener ( update_frame_listener );
						delete update_frame_listener;
					}
				}
		};

	} // namespace Graphics
} // namespace UnknownEngine
