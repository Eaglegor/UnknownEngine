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

		OgreRenderSubsystem::OgreRenderSubsystem ( const UnknownEngine::Graphics::OgreRenderSubsystem::Descriptor& desc, UnknownEngine::Core::LogHelper* log_helper )
			: log_helper ( log_helper )
		{

			ogre_log_manager = new Ogre::LogManager;
			ogre_log_manager->createLog(desc.ogre_log_filename, true, false, false);

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
			}

		}

		OgreRenderSubsystem::~OgreRenderSubsystem()
		{
			root->shutdown();
			delete root;

			ogre_log_manager->destroyLog("DefaultLog");
			delete ogre_log_manager;
			
		}

		
	} // namespace Graphics
} // namespace UnknownEngine
