#pragma once

#include <InlineSpecification.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/LogMessage.h>

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
	}

	namespace Graphics
	{

		class OgreRenderSubsystem
		{
			public:

				struct Descriptor
				{
					std::string ogre_plugins_filename;
					std::string ogre_config_filename;
					std::string ogre_log_filename;
					std::string render_window_name;
					boost::optional<std::string> ogre_resources_filename;
					
					bool show_config_dialog;
					
					Descriptor() :
						render_window_name ( "Untitled window" ),
						ogre_config_filename ( "ogre.cfg" ),
						ogre_log_filename ( "Ogre.log" ),
						ogre_plugins_filename ( "plugins.cfg" ),
						show_config_dialog(false)
					{}

				};

				explicit OgreRenderSubsystem ( const UnknownEngine::Graphics::OgreRenderSubsystem::Descriptor& desc, UnknownEngine::Core::LogHelper* log_helper = nullptr );
				virtual ~OgreRenderSubsystem();
				void onFrameUpdated ( const Core::UpdateFrameMessage& msg );

				void loadResourcesFile(const std::string &filename);
				
				UNKNOWNENGINE_INLINE
				Ogre::SceneManager* getSceneManager()
				{
					return scene_manager;
				}
				Ogre::RenderWindow* getRenderWindow()
				{
					return render_window;
				}

			private:
				Ogre::Root* root;
				Ogre::SceneManager* scene_manager;
				Ogre::RenderWindow* render_window;
				Core::LogHelper* log_helper;
				Ogre::LogManager* ogre_log_manager;
				
				int counter;
		};

	} // namespace Graphics
} // namespace UnknownEngine
