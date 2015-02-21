#pragma once

#include <unordered_map>
#include <memory>

#include <InlineSpecification.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/LogMessage.h>
#include <Descriptors/OgreRenderSubsystemDescriptor.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>

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
		class ILogger;
	}

	namespace Graphics
	{

		struct WindowResizedMessage;
		struct GetOgreRenderTargetMessage;

		class OgreRenderCallback;

		class OgreUpdateFrameListener;
		class OgreRenderFrameListener;
		class OgreRenderWindowWrapper;
		
		class OgreRenderSubsystem : public ComponentInterfaces::UpdateFrameListenerComponent
		{
			public:

				explicit OgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Core::ILogger* logger, Core::EngineContext* engine_context );
				virtual ~OgreRenderSubsystem();
				
				void loadResourcesFile(const std::string &filename);

				virtual void start(const std::string &name);
				virtual void stop();
				
				UNKNOWNENGINE_INLINE
				Ogre::SceneManager* getSceneManager()
				{
					return scene_manager;
				}
				
				UNKNOWNENGINE_INLINE
				Ogre::Root* getOgreRoot()
				{
					return root;
				}
				
				const char* getName()
				{
					return name.c_str();
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
				
				virtual void onUpdateFrame ( Math::Scalar dt );
				
			private:
				friend class OgreUpdateFrameListener;
				
				void initOgre(const std::string &subsystem_name);
				void shutdownOgre();
				std::string name;
				
				//virtual void onFrameUpdated ( const Core::UpdateFrameMessage& msg );
				virtual void onWindowResized( const Graphics::WindowResizedMessage& msg );
				void onGetOgreRenderTarget(const GetOgreRenderTargetMessage& msg);
				
				std::unordered_map<std::string, OgreRenderWindowWrapper*> render_windows;
				
				Ogre::Root* root;
				Ogre::SceneManager* scene_manager;
				Core::ILogger* logger;
				Ogre::LogManager* ogre_log_manager;
				
				Core::EngineContext* engine_context;
		
				std::unique_ptr<Core::BaseMessageListener> listener;
				
				OgreRenderSubsystemDescriptor desc;
				
				std::unique_ptr<boost::thread> rendering_thread;
				std::unique_ptr<OgreRenderFrameListener> frame_listener;
				Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
		};

	} // namespace Graphics
} // namespace UnknownEngine
