#pragma once

#include <InlineSpecification.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/LogMessage.h>
#include <functional>

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
					
					bool separate_rendering_thread;
					
					bool show_config_dialog;
					
					Descriptor() :
						render_window_name ( "Untitled window" ),
						ogre_config_filename ( "ogre.cfg" ),
						ogre_log_filename ( "Ogre.log" ),
						ogre_plugins_filename ( "plugins.cfg" ),
						show_config_dialog(false),
						separate_rendering_thread(true)
					{}

				};

				explicit OgreRenderSubsystem ( const OgreRenderSubsystem::Descriptor& desc, Core::LogHelper* log_helper, Core::EngineContext* engine_context );
				virtual ~OgreRenderSubsystem();
				void onFrameUpdated ( const Core::UpdateFrameMessage& msg );

				void loadResourcesFile(const std::string &filename);

				void start();
				void stop();
				
#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
				void addSynchronizeCallback(const std::string &name, const std::function<void()> &callback);
				void removeSynchronizeCallback( const std::string& name );
				void addInitCallback(const std::string &name, const std::function<void()> &callback);
				void addRemoveCallback(const std::string &name, const std::function<void()> &callback);
#endif
				
				UNKNOWNENGINE_INLINE
				bool hasSeparateRenderThreadEnabled(){ 
#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
					return desc.separate_rendering_thread; 
#else
					return false;
#endif
				}
				
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
				
				Core::EngineContext* engine_context;
				OgreUpdateFrameListener* update_frame_listener;
		
				Descriptor desc;
				
#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
				std::unique_ptr<boost::thread> rendering_thread;
				std::unique_ptr< OgreRenderCallback > render_synchronize_callback;
#endif
				
				int counter;
		};

	} // namespace Graphics
} // namespace UnknownEngine
