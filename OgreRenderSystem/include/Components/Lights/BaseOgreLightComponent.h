#pragma once

#include <Components/BaseOgreComponent.h>
#include <Components/ConcurrentTransformAdapter.h>
#include <Descriptors/Components/Lights/OgreLightSettings.h>
#include <ComponentInterfaces/Transform/MovableComponent.h>
#include <ComponentInterfaces/Transform/TransformNotifierComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>

namespace Ogre
{
	class Light;
	class SceneNode;
}

namespace UnknownEngine
{
	namespace Core
	{

		struct TransformChangedMessage;
		class EngineContext;
	}

	namespace Graphics
	{

		class OgreRenderSubsystem;
		class BaseOgreLightComponentListener;
	
		class BaseOgreLightComponent : 
		public BaseOgreComponent,
		public ComponentInterfaces::MovableComponent
		{
			public:
				BaseOgreLightComponent ( const std::string& name, OgreRenderSubsystem* render_subsystem, const OgreLightSettings& light_settings, Core::IComponent* transform_provider );
				virtual ~BaseOgreLightComponent();
				
				virtual void setOrientation ( const Math::Quaternion& quaternion );
				virtual void setPosition ( const Math::Vector3& position );
				virtual void setTransform ( const Math::Transform& transform );
				
				virtual void _update();
				
			protected:
				virtual void internalInit() override;
				virtual void internalShutdown() override;

				OgreLightSettings light_settings;
				
				Ogre::Light* ogre_light;
				Ogre::SceneNode* ogre_scene_node;
				
				Core::ComponentInterfacePtr<ComponentInterfaces::TransformNotifierComponent> transform_provider;
				
				ConcurrentTransformAdapter transform_adapter;
		};
	}
}
