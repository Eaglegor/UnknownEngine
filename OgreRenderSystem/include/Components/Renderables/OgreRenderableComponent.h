#pragma once

#include <OgreRenderSubsystem_fwd.h>
#include <Components/BaseOgreComponent.h>
#include <Exception.h>
#include <Descriptors/Components/Renderables/OgreRenderableComponentDescriptor.h>

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

		const Core::ComponentType OGRE_RENDERABLE_COMPONENT_TYPE = "Graphics.Renderable";

		class OgreRenderableComponent: public BaseOgreComponent
		{
			public:

				UNKNOWNENGINE_SIMPLE_EXCEPTION(NoMeshDataProvidedException);
				
				OgreRenderableComponent ( const std::string &name, const OgreRenderableComponentDescriptor &desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext *engine_context );
				virtual ~OgreRenderableComponent();
			
				virtual Core::ComponentType getType() override;

				virtual void addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message );
				
				virtual void onTransformChanged ( const Core::TransformChangedMessage &message );
				virtual void doChangeMaterial ( const ChangeMaterialActionMessage &message );

				virtual void processMessages();
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			protected:
				virtual void internalInit(const Core::Entity* parent_entity) override;
				virtual void internalShutdown() override;
				
				virtual void registerMessageProcessors ( Core::BaseMessageListener* message_listener );
				
			private:
				OgreRenderableComponentDescriptor desc;
				
				OgreRenderableComponentListener* listener;
				
				Ogre::Entity* entity;
				Ogre::SceneNode* scene_node;
		};

	} // namespace Graphics
} // namespace UnknownEngine
