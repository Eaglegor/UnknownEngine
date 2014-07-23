#pragma once

#include <string>
#include <Objects/Component.h>
#include <Mesh/MeshData.h>

namespace Ogre
{
	class Entity;
	class SceneNode;
}

namespace UnknownEngine {
	namespace Graphics {

		class OgreRenderSubsystem;
		class OgreMeshPtrProvider;

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
				 * This method is intended to register listeners and start processing messages
				 * It's called when the entity is started. Is called by entity.
				 *
				 */
				virtual void start();

				/**
				 *  @brief Is called when the parent entity is about to be destroyed
				 *
				 * This method is intended to unregister listeners and stop processing messages
				 * Is called by entity.
				 *
				 */
				virtual void shutdown();

				/**
				 * @brief Returns the type of component
				 * @return Type of component
				 */
				virtual Core::ComponentType getType();

				OgreRenderableComponent(const std::string &name, const Descriptor &desc, OgreRenderSubsystem* render_system);
				virtual ~OgreRenderableComponent();

			private:
				const Core::ComponentType type;
				OgreRenderSubsystem* render_system;
				OgreMeshPtrProvider* mesh_data_provider;
				Ogre::Entity* entity;
				Ogre::SceneNode* scene_node;
				std::string name;
		};

	} // namespace Graphics
} // namespace UnknownEngine
