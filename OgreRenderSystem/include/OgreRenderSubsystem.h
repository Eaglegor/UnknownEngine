#pragma once

#include <InlineSpecification.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <Components/OgreRenderableComponent.h>

namespace Ogre
{
	class Root;
	class SceneManager;
	class RenderWindow;
}

namespace UnknownEngine {
	namespace Graphics {

		class OgreRenderSubsystem
		{
			public:

				struct Descriptor
				{
					std::string config_filename;
					std::string render_window_name;
				};

				OgreRenderSubsystem(const Descriptor& desc);
				void onFrameUpdated(const Core::UpdateFrameMessage& msg);

				UNKNOWNENGINE_INLINE
				Ogre::SceneManager* getSceneManager(){return scene_manager;}

			private:
				Ogre::Root* root;
				Ogre::SceneManager* scene_manager;
				Ogre::RenderWindow* render_window;
		};

	} // namespace Graphics
} // namespace UnknownEngine
