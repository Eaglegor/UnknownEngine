#pragma once

#include <Components/BaseOgreComponent.h>
#include <Components/ConcurrentTransformAdapter.h>
#include <ComponentSystem/ComponentType.h>
#include <AlignedNew.h>
#include <Descriptors/Components/Cameras/OgreCameraComponentDescriptor.h>
#include <Exception.h>
#include <LogHelper.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/RenderSystem/Ogre/IOgreRenderWindowComponent.h>
#include <ComponentInterfaces/Transform/TransformNotifierComponent.h>
#include <ComponentInterfaces/Transform/MovableComponent.h>
#include <Spinlock.h>

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

		UNKNOWNENGINE_ALIGNED_CLASS(16) OgreCameraComponent : 
		public BaseOgreComponent,
		public ComponentInterfaces::MovableComponent
		{
			public:
				UNKNOWNENGINE_SIMPLE_EXCEPTION(RenderWindowNotFound);
				
				OgreCameraComponent ( const std::string &name, const OgreCameraComponentDescriptor& desc, OgreRenderSubsystem *render_subsystem );
				virtual ~OgreCameraComponent();
				
				constexpr static const char* getTypeName(){return "Ogre.Camera";}
				virtual Core::ComponentType getType() const override {return getTypeName();}

				virtual void _update() override;
				
				virtual void setOrientation ( const Math::Quaternion & quaternion ) override;
				virtual void setPosition ( const Math::Vector3 & position ) override;
				virtual void setTransform ( const Math::Transform & transform ) override;
				
				virtual IComponentInterface * getInterface ( const Core::ComponentType & type );
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			protected:
				virtual void internalInit () override;
				virtual void internalShutdown (  ) override;
				
			private:
				OgreCameraComponentDescriptor desc;
				
				Ogre::SceneNode *scene_node;
				Ogre::Camera *camera;
				
				Core::LogHelper logger;
				
				Core::ComponentInterfacePtr<ComponentInterfaces::IOgreRenderWindowComponent> render_window;
				
				ConcurrentTransformAdapter transform_adapter;
		};
	}
}
