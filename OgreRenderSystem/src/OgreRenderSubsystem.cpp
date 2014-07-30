#include <stdafx.h>

#include <Ogre.h>
#include <OgreRenderSubsystem.h>
#include <LogHelper.h>

namespace UnknownEngine {
	namespace Graphics {

		OgreRenderSubsystem::OgreRenderSubsystem( const OgreRenderSubsystem::Descriptor& desc, Core::LogHelper* log_helper )
		:log_helper(log_helper)
		{
		  
			root = new Ogre::Root(desc.ogre_plugins_filename, desc.ogre_config_filename, desc.ogre_log_filename);
			root->showConfigDialog();
			scene_manager = root->createSceneManager(Ogre::ST_GENERIC);
			render_window = root->initialise(true, desc.render_window_name);
		}

		void OgreRenderSubsystem::onFrameUpdated(const Core::UpdateFrameMessage &msg)
		{
			//LOG_DEBUG(log_helper, "Rendering frame");
			if(msg.stage == Core::UpdateFrameMessage::PROCESSING)
			{
			  root->renderOneFrame();
			}
			
		}

	} // namespace Graphics
} // namespace UnknownEngine
