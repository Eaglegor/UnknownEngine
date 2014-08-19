#pragma once

#include <InlineSpecification.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/LogMessage.h>
#include <Descriptors/OgreRenderSubsystemDescriptor.h>
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

		class BaseOgreRenderSubsystem
		{
			public:

				explicit BaseOgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Core::LogHelper* log_helper, Core::EngineContext* engine_context );
				virtual ~BaseOgreRenderSubsystem();
				
				virtual void onFrameUpdated ( const Core::UpdateFrameMessage& msg );

				void loadResourcesFile(const std::string &filename);

				virtual void start() = 0;
				virtual void stop() = 0;
				
				UNKNOWNENGINE_INLINE
				Ogre::SceneManager* getSceneManager()
				{
					return scene_manager;
				}
				Ogre::RenderWindow* getRenderWindow()
				{
					return render_window;
				}
				

			protected:
				Ogre::Root* root;
				Ogre::SceneManager* scene_manager;
				Ogre::RenderWindow* render_window;
				Core::LogHelper* log_helper;
				Ogre::LogManager* ogre_log_manager;
				
				Core::EngineContext* engine_context;
				OgreUpdateFrameListener* update_frame_listener;
		
				OgreRenderSubsystemDescriptor desc;
		};

	} // namespace Graphics
} // namespace UnknownEngine
