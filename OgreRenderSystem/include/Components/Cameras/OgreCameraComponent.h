#pragma once

#include <Components/BaseOgreComponent.h>
#include <ComponentSystem/ComponentType.h>
#include <AlignedNew.h>
#include <Descriptors/Components/Cameras/OgreCameraComponentDescriptor.h>
#include <Exception.h>

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
		class OgreRenderSubsystem;

		const Core::ComponentType OGRE_CAMERA_COMPONENT_TYPE = "Graphics.Camera";

		UNKNOWNENGINE_ALIGNED_CLASS(16) OgreCameraComponent : public BaseOgreComponent
		{
			public:

				UNKNOWNENGINE_SIMPLE_EXCEPTION(RenderWindowNotFound);
				
				OgreCameraComponent ( const std::string &name, const OgreCameraComponentDescriptor& desc, OgreRenderSubsystem *render_subsystem, Core::EngineContext* engine_context );
				virtual ~OgreCameraComponent();
				
				virtual Core::ComponentType getType() const override;				

				void onTransformChanged ( const Core::TransformChangedMessage& msg );
				void doLookAt ( const CameraLookAtActionMessage& msg );

				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			protected:
				virtual void internalInit ( const Core::IEntity *parent_entity ) override;
				virtual void internalShutdown (  ) override;
				
				virtual void initMessageListenerBuffers ( bool can_be_multi_threaded ) override;
				
			private:
				OgreCameraComponentDescriptor desc;
				
				Ogre::SceneNode *scene_node;
				Ogre::Camera *camera;
		};
	}
}
