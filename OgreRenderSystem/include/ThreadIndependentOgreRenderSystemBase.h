#pragma once

#include <unordered_map>
#include <memory>

#include <InlineSpecification.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/LogMessage.h>
#include <Descriptors/OgreRenderSubsystemDescriptor.h>
#include <MessageSystem/MessageListenerDesc.h>


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
		class EngineContext;
		class BaseMessageListener;
	}

	namespace Utils
	{
		class LogHelper;
	}
	
	namespace Graphics
	{

		struct WindowResizedMessage;

		class OgreRenderCallback;

		class OgreUpdateFrameListener;

		class ThreadIndependentOgreRenderSystemBase
		{
			public:

				explicit ThreadIndependentOgreRenderSystemBase ( const OgreRenderSubsystemDescriptor& desc, Utils::LogHelper* log_helper, Core::EngineContext* engine_context );
				virtual ~ThreadIndependentOgreRenderSystemBase();
				
				virtual void onFrameUpdated ( const Core::UpdateFrameMessage& msg );
				virtual void onWindowResized( const Graphics::WindowResizedMessage& msg );
				
				
				void loadResourcesFile(const std::string &filename);

				virtual void start(const std::string &name, const Core::ReceivedMessageDescriptorsList& received_messages) = 0;
				virtual void stop() = 0;
				
				UNKNOWNENGINE_INLINE
				Ogre::SceneManager* getSceneManager()
				{
					return scene_manager;
				}
				
				Ogre::RenderWindow* getRenderWindow(const std::string &name);
				
			protected:

				
				
				void initOgre(const std::string &subsystem_name);
				void shutdownOgre();
				
				std::unordered_map<std::string, Ogre::RenderWindow*> render_windows;
				
				Ogre::Root* root;
				Ogre::SceneManager* scene_manager;
				Utils::LogHelper* log_helper;
				Ogre::LogManager* ogre_log_manager;
				
				Core::EngineContext* engine_context;
		
				std::unique_ptr<Core::BaseMessageListener> listener;
				
				OgreRenderSubsystemDescriptor desc;
		};

	} // namespace Graphics
} // namespace UnknownEngine
