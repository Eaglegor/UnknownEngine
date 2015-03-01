#pragma once

#include <Components/BaseOgreComponent.h>
#include <Components/ConcurrentTransformAdapter.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <Exception.h>
#include <Descriptors/Components/Renderables/OgreRenderableComponentDescriptor.h>
#include <LogHelper.h>
#include <ComponentInterfaces/Transform/MovableComponent.h>
#include <ComponentInterfaces/RenderSystem/IRenderable.h>
#include <ComponentInterfaces/Transform/TransformNotifierComponent.h>
#include <Spinlock.h>

namespace Ogre
{
	class Entity;
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
		class OgreRenderableComponentListener;
		struct ChangeMaterialActionMessage;
		class OgreRenderSubsystem;

		UNKNOWNENGINE_ALIGNED_CLASS(16) OgreRenderableComponent: 
		public BaseOgreComponent,
		public ComponentInterfaces::MovableComponent,
		public ComponentInterfaces::IRenderable
		{
			public:

				UNKNOWNENGINE_SIMPLE_EXCEPTION(NoMeshDataProvidedException);
				
				OgreRenderableComponent ( const std::string &name, const OgreRenderableComponentDescriptor &desc, OgreRenderSubsystem* render_subsystem );
				virtual ~OgreRenderableComponent();

				constexpr static const char* getTypeName(){return "Ogre.Renderable";}
 				virtual Core::ComponentType getType() const override {return getTypeName();}
				
				virtual void _update() override;

				virtual void setOrientation ( const Math::Quaternion & quaternion ) override;
				virtual void setPosition ( const Math::Vector3 & position ) override;
				virtual void setTransform ( const Math::Transform & transform ) override;
				
				virtual void setMaterialName ( const char * material_name ) override;
				
				virtual IComponentInterface * getInterface ( const Core::ComponentType & type ) override;
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			protected:
				virtual void internalInit() override;
				virtual void internalShutdown() override;

			private:
				Core::ComponentInterfacePtr<ComponentInterfaces::TransformNotifierComponent> transform_provider;
				OgreRenderableComponentDescriptor desc;
				
				Ogre::Entity* entity;
				Ogre::SceneNode* scene_node;
				
				Core::LogHelper logger;
			
				ConcurrentTransformAdapter transform_adapter;
		};

	} // namespace Graphics
} // namespace UnknownEngine
