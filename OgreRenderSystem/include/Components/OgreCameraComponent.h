#pragma once

#include <Objects/Component.h>
#include <ComponentType.h>
#include <MessageSystem/MessagingPoliciesManager.h>
#include <ExportedMessages/LogMessage.h>
#include <Transform/Transform.h>

namespace Ogre
{
	class Camera;
	class SceneNode;
}

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
		class TransformChangedMessage;
		class ReceivedMessageDesc;
		class LogHelper;
	}

	namespace Graphics
	{

		class OgreRenderSubsystem;
		class OgreCameraComponentListener;
		class CameraLookAtActionMessage;

		const Core::ComponentType OGRE_CAMERA_COMPONENT_TYPE = "Graphics.Camera";

		class OgreCameraComponent : public UnknownEngine::Core::Component
		{
			public:

				struct Descriptor
				{
					Core::LogMessage::Severity log_level;
					Core::Transform initial_transform;
					
					boost::optional<Math::Vector3> initial_look_at;
					
					Descriptor():
					log_level(Core::LogMessage::LOG_SEVERITY_NONE){}
				};

				virtual UnknownEngine::Core::ComponentType getType();
				virtual void shutdown();
				virtual void start();
				virtual void init ( const UnknownEngine::Core::Entity *parent_entity );

				void onTransformChanged ( const Core::TransformChangedMessage& msg );
				void doLookAt ( const CameraLookAtActionMessage& msg );

				OgreCameraComponent ( const std::string &name, const Descriptor& desc, OgreRenderSubsystem *render_subsystem, Core::EngineContext* engine_context );
				virtual ~OgreCameraComponent();

				virtual void addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message );

			private:
				OgreRenderSubsystem *render_subsystem;
				Ogre::SceneNode *scene_node;
				Ogre::Camera *camera;
				Core::EngineContext* engine_context;
				const Core::ComponentType type;
				OgreCameraComponentListener* listener;
				Core::MessagingPoliciesManager messaging_policies_manager;
				Descriptor desc;
				
				Core::LogHelper *log_helper;

		};
	}
}
