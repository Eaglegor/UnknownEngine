#pragma once

#include <string>
#include <Objects/Component.h>
#include <Mesh/MeshData.h>
#include <Listeners/OgreRenderableComponentListener.h>

namespace Ogre
{
	class Entity;
	class SceneNode;
}

namespace UnknownEngine {

	namespace Core
	{
		class TransformChangedMessage;
		class IMessageListener;
		class EngineContext;
	}

	namespace Graphics {

		class OgreRenderSubsystem;
		class OgreMeshPtrProvider;
		class ChangeMaterialActionMessage;
		class OgreRenderableComponentListener;

		const Core::ComponentType OGRE_RENDERABLE_COMPONENT_TYPE = "Renderable";

		class OgreRenderableComponent: public Core::Component
		{
			public:

				struct Descriptor
				{
					OgreMeshPtrProvider* mesh_data_provider;
					std::string material_name;
				};

				/**
				 * @brief Is called when the component is created
				 *
				 * The init stuff must be done in this method. Is called by parent entity after component addition.
				 *
				 */
				virtual void init(const Core::Entity* parent_entity);

				/**
				 *  @brief Is called when the parent entity is started
				 *
				 *  At this moment it's known that all components of the entity are created. Start processing logic.
				 *
				 */
				virtual void start();

				/**
				 *  @brief Is called when the parent entity is about to be destroyed
				 *
				 * Stop any logic there. Prepare to destruction;
				 * Is called by entity.
				 *
				 */
				virtual void shutdown();

				/**
				 * @brief Returns the type of component
				 * @return Type of component
				 */
				virtual Core::ComponentType getType();

				virtual void onTransformChanged(const Core::TransformChangedMessage &message);
				virtual void doChangeMaterial(const ChangeMaterialActionMessage &message);

				OgreRenderableComponent(const std::string &name, const Descriptor &desc, OgreRenderSubsystem* render_system, Core::EngineContext *engine_context);
				virtual ~OgreRenderableComponent();

				Core::IMessageListener* createListener(const std::string &listener_name, Core::EngineContext* engine_context);

			private:
				const Core::ComponentType type;
				OgreRenderSubsystem* render_system;
				std::vector<OgreRenderableComponentListener> listeners;
				OgreMeshPtrProvider* mesh_data_provider;
				Ogre::Entity* entity;
				Ogre::SceneNode* scene_node;
		};

	} // namespace Graphics
} // namespace UnknownEngine
