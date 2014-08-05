#include <stdafx.h>

#include <Ogre.h>
#include <OgreRenderSubsystem.h>
#include <LogHelper.h>
#include <EngineContext.h>

#include <MessageSystem/MessageSystemParticipantDictionary.h>
#include <MessageSystem/MessageDispatcher.h>

#include <ExportedMessages/StopEngineActionMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderSubsystem::OgreRenderSubsystem ( const UnknownEngine::Graphics::OgreRenderSubsystem::Descriptor& desc, UnknownEngine::Core::EngineContext* engine_context, UnknownEngine::Core::LogHelper* log_helper )
			: log_helper ( log_helper ), counter(0), engine_context(engine_context)
		{

			root = new Ogre::Root ( desc.ogre_plugins_filename, desc.ogre_config_filename, desc.ogre_log_filename );
			root->showConfigDialog();
			scene_manager = root->createSceneManager ( Ogre::ST_GENERIC );
			render_window = root->initialise ( true, desc.render_window_name );
		}

		void OgreRenderSubsystem::onFrameUpdated ( const Core::UpdateFrameMessage &msg )
		{
			//LOG_DEBUG(log_helper, "Rendering frame");
			if ( msg.stage == Core::UpdateFrameMessage::PROCESSING )
			{
				Ogre::WindowEventUtilities::messagePump();
				root->renderOneFrame();
				++counter;
				if(counter == 2000) {
				  engine_context->getMessageSystemParticipantDictionary()->registerNewMessageParticipant("OgreRenderSystem");
				  Core::StopEngineActionMessage msg;
				  Core::StopEngineActionMessagePacker packer(Core::MessageSystemParticipantId("OgreRenderSystem"));
				  engine_context->getMessageDispatcher()->deliverMessage(packer.packMessage(msg));
				}
			}

		}

	} // namespace Graphics
} // namespace UnknownEngine
