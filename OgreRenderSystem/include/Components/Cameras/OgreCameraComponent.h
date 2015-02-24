#pragma once

#include <Components/BaseOgreComponent.h>
#include <ComponentSystem/ComponentType.h>
#include <AlignedNew.h>
#include <Descriptors/Components/Cameras/OgreCameraComponentDescriptor.h>
#include <Exception.h>
#include <LogHelper.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/Ogre/IOgreRenderWindowComponent.h>
#include <ComponentInterfaces/Transform/TransformHolderComponent.h>

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

		UNKNOWNENGINE_ALIGNED_CLASS(16) OgreCameraComponent : public BaseOgreComponent
		{
			public:
				UNKNOWNENGINE_SIMPLE_EXCEPTION(RenderWindowNotFound);
				
				OgreCameraComponent ( const std::string &name, const OgreCameraComponentDescriptor& desc, OgreRenderSubsystem *render_subsystem );
				virtual ~OgreCameraComponent();
				
				constexpr static const char* getTypeName(){return "Ogre.Camera";}
				virtual Core::ComponentType getType() const override {return getTypeName();}

				void doLookAt ( const CameraLookAtActionMessage& msg );

				virtual void _update() override;
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			protected:
				virtual void internalInit ( const Core::IEntity *parent_entity ) override;
				virtual void internalShutdown (  ) override;
				
			private:
				OgreCameraComponentDescriptor desc;
				
				Ogre::SceneNode *scene_node;
				Ogre::Camera *camera;
				
				Core::LogHelper logger;
				
				Core::ComponentInterfacePtr<ComponentInterfaces::IOgreRenderWindowComponent> render_window;
				Core::ComponentInterfacePtr<ComponentInterfaces::TransformHolderComponent> transform_provider;
		};
	}
}
