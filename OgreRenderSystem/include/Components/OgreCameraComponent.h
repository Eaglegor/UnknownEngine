#pragma once

#include <Objects/Component.h>
#include <ComponentType.h>
#include <MessageSystem/MessagingPoliciesManager.h>

namespace Ogre
{
	class Camera;
	class SceneNode;
}

namespace UnknownEngine
{
  
	namespace Core {
	  class EngineContext;
	  class TransformChangedMessage;
	  class ReceivedMessageDesc;
	}
  
	namespace Graphics
	{

		class OgreRenderSubsystem;
		class OgreCameraComponentListener;

		const Core::ComponentType OGRE_CAMERA_COMPONENT_TYPE = "Graphics.Camera";
		
		class OgreCameraComponent : public UnknownEngine::Core::Component
		{
			public:
			  
			        class Descriptor
			        {
				};
			  
				virtual UnknownEngine::Core::ComponentType getType();
				virtual void shutdown();
				virtual void start();
				virtual void init ( const UnknownEngine::Core::Entity *parent_entity );
				
				void onTransformChanged(const Core::TransformChangedMessage& msg);
				
				OgreCameraComponent ( const std::string &name, const Descriptor& desc, OgreRenderSubsystem *render_subsystem, Core::EngineContext* engine_context );
				virtual ~OgreCameraComponent();
				
				virtual void addReceivedMessageType(const Core::ReceivedMessageDesc &received_message);
				
			private:
				OgreRenderSubsystem *render_subsystem;
				Ogre::SceneNode *scene_node;
				Ogre::Camera *camera;
				Core::EngineContext* engine_context;
				const Core::ComponentType type;
				OgreCameraComponentListener* listener;
				Core::MessagingPoliciesManager messaging_policies_manager;
				
		};
	}
}
