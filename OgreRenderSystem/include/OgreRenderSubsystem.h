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
  
	namespace Core
	{
	  class LogHelper;
	}
  
	namespace Graphics {

		class OgreRenderSubsystem
		{
			public:

				struct Descriptor
				{
					std::string ogre_plugins_filename;
					std::string ogre_config_filename;
					std::string ogre_log_filename;
					std::string render_window_name;
				};

				explicit OgreRenderSubsystem(const Descriptor& desc, Core::EngineContext* engine_context, Core::LogHelper* log_helper = nullptr);
				void onFrameUpdated(const Core::UpdateFrameMessage& msg);

				UNKNOWNENGINE_INLINE
				Ogre::SceneManager* getSceneManager(){return scene_manager;}
				Ogre::RenderWindow* getRenderWindow(){return render_window;}

			private:
				Ogre::Root* root;
				Ogre::SceneManager* scene_manager;
				Ogre::RenderWindow* render_window;
				Core::LogHelper* log_helper;
				Core::EngineContext* engine_context;
				
				int counter;
		};

	} // namespace Graphics
} // namespace UnknownEngine
