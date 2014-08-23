#pragma once

#include <OgreRenderSubsystem_fwd.h>
#include <Components/BaseOgreComponent.h>
#include <ComponentType.h>
#include <AlignedNew.h>
#include <Descriptors/Components/Cameras/OgreCameraComponentDescriptor.h>

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
		struct TransformChangedMessage;
		struct ReceivedMessageDesc;
	}

	namespace Graphics
	{

		class OgreCameraComponentListener;
		struct CameraLookAtActionMessage;

		const Core::ComponentType OGRE_CAMERA_COMPONENT_TYPE = "Graphics.Camera";

		class OgreCameraComponent : public BaseOgreComponent
		{
			public:

				OgreCameraComponent ( const std::string &name, const OgreCameraComponentDescriptor& desc, OgreRenderSubsystem *render_subsystem, Core::EngineContext* engine_context );
				virtual ~OgreCameraComponent();
				
				virtual UnknownEngine::Core::ComponentType getType() override;				

				virtual void addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message );
				
				void onTransformChanged ( const Core::TransformChangedMessage& msg );
				void doLookAt ( const CameraLookAtActionMessage& msg );

				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			protected:
				virtual void internalInit ( const UnknownEngine::Core::Entity *parent_entity ) override;
				virtual void internalShutdown (  ) override;
				
			private:
				OgreCameraComponentDescriptor desc;
				
				OgreCameraComponentListener* listener;
				
				Ogre::SceneNode *scene_node;
				Ogre::Camera *camera;
		};
	}
}
