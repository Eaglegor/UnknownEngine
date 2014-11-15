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
		class OgreRenderFrameListener;

		class OgreRenderSubsystem
		{
			public:

				explicit OgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Utils::LogHelper* log_helper, Core::EngineContext* engine_context );
				virtual ~OgreRenderSubsystem();
				
				virtual void onFrameUpdated ( const Core::UpdateFrameMessage& msg );
				virtual void onWindowResized( const Graphics::WindowResizedMessage& msg );
				
				
				void loadResourcesFile(const std::string &filename);

				virtual void start(const std::string &name, const Core::ReceivedMessageDescriptorsList& received_messages);
				virtual void stop();
				
				UNKNOWNENGINE_INLINE
				Ogre::SceneManager* getSceneManager()
				{
					return scene_manager;
				}
				
				Ogre::RenderWindow* getRenderWindow(const std::string &name);
				
				void update();
				
				void addSynchronizeCallback ( const std::string &name, const std::function<void() > &callback );
				
				void removeSynchronizeCallback ( const std::string& name );
				
				void addInitCallback ( const std::function<void() > &callback );
				
				void addShutdownCallback ( const std::function<void() > &callback );
				
				void addRemoveCallback ( const std::function< void() >& callback );

				UNKNOWNENGINE_INLINE
				bool hasSeparateRenderThreadEnabled()
				{
					return desc.separate_rendering_thread;
				}
				
			private:
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
				
				std::unique_ptr<boost::thread> rendering_thread;
				std::unique_ptr<OgreRenderFrameListener> frame_listener;
		};

	} // namespace Graphics
} // namespace UnknownEngine
