#include <stdafx.h>

#include <OgreRenderSubsystem.h>

namespace UnknownEngine {
	namespace Graphics {

		OgreRenderSubsystem::OgreRenderSubsystem(const Descriptor &desc)
		{
			root = new Ogre::Root(desc.config_filename);
			scene_manager = root->createSceneManager(Ogre::ST_GENERIC);
			render_window = root->initialise(true, desc.render_window_name);
		}

		void OgreRenderSubsystem::onFrameUpdated(const Core::UpdateFrameMessage &msg)
		{
			root->renderOneFrame();
		}

	} // namespace Graphics
} // namespace UnknownEngine
