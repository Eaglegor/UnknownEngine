#pragma once

#include <InlineSpecification.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/LogMessage.h>
#include <Descriptors/OgreRenderSubsystemDescriptor.h>

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
		class BaseMessageListener;
	}

	namespace Graphics
	{

		struct WindowResizedMessage;

		class OgreRenderCallback;

		class OgreUpdateFrameListener;

		class ThreadIndependentOgreRenderSystemBase
		{
			public:

				explicit ThreadIndependentOgreRenderSystemBase ( const OgreRenderSubsystemDescriptor& desc, Core::LogHelper* log_helper, Core::EngineContext* engine_context );
				virtual ~ThreadIndependentOgreRenderSystemBase();
				
				virtual void onFrameUpdated ( const Core::UpdateFrameMessage& msg );
				virtual void onWindowResized( const Graphics::WindowResizedMessage& msg );
				
				
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
				
				void initOgre();
				void shutdownOgre();
				
				Ogre::Root* root;
				Ogre::SceneManager* scene_manager;
				Ogre::RenderWindow* render_window;
				Core::LogHelper* log_helper;
				Ogre::LogManager* ogre_log_manager;
				
				Core::EngineContext* engine_context;
		
				std::unique_ptr<Core::BaseMessageListener> listener;
				
				OgreRenderSubsystemDescriptor desc;
		};

	} // namespace Graphics
} // namespace UnknownEngine
