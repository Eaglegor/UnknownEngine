#pragma once

#include <Components/BaseOgreComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <Exception.h>
#include <Descriptors/Components/Renderables/OgreRenderableComponentDescriptor.h>
#include <LogHelper.h>

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

		UNKNOWNENGINE_ALIGNED_CLASS(16) OgreRenderableComponent: public BaseOgreComponent
		{
			public:

				UNKNOWNENGINE_SIMPLE_EXCEPTION(NoMeshDataProvidedException);
				
				OgreRenderableComponent ( const std::string &name, const OgreRenderableComponentDescriptor &desc, OgreRenderSubsystem* render_subsystem );
				virtual ~OgreRenderableComponent();

				constexpr static const char* getTypeName(){return "Ogre.Renderable";}
 				virtual Core::ComponentType getType() const override {return getTypeName();}
				
				virtual void _update() override;

				virtual void onTransformChanged ( const Core::TransformChangedMessage &message );
				virtual void doChangeMaterial ( const ChangeMaterialActionMessage &message );

				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			protected:
				virtual void internalInit(const Core::IEntity* parent_entity) override;
				virtual void internalShutdown() override;

			private:
				Core::ComponentInterfacePtr<ComponentInterfaces::TransformHolderComponent> transform_provider;
				OgreRenderableComponentDescriptor desc;
				
				Ogre::Entity* entity;
				Ogre::SceneNode* scene_node;
				
				Core::LogHelper logger;
		};

	} // namespace Graphics
} // namespace UnknownEngine
