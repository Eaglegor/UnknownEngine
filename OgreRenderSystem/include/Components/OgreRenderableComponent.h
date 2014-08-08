#pragma once

#include <string>
#include <Objects/Component.h>
#include <Mesh/MeshData.h>
#include <Listeners/OgreRenderableComponentListener.h>
#include <MessageSystem/MessagingPoliciesManager.h>
#include <ExportedMessages/LogMessage.h>

namespace Ogre
{
	class Entity;
	class SceneNode;
}

namespace UnknownEngine
{

	namespace Core
	{
		class TransformChangedMessage;
		class IMessageListener;
		class EngineContext;
		class ReceivedMessageDesc;
		class LogHelper;
	}

	namespace Graphics
	{

		class OgreRenderSubsystem;
		class OgreMeshPtrProvider;
		class ChangeMaterialActionMessage;
		class OgreRenderableComponentListener;

		const Core::ComponentType OGRE_RENDERABLE_COMPONENT_TYPE = "Graphics.Renderable";

		class OgreRenderableComponent: public Core::Component
		{
			public:

				struct Descriptor
				{
					OgreMeshPtrProvider* mesh_data_provider;
					std::string material_name;
					Core::Transform initial_transform;
					
					Core::LogMessage::Severity log_level;

					Descriptor() :
						material_name ( "BaseWhiteNoLighting" ),
						mesh_data_provider ( nullptr ),
						initial_transform ( Core::Transform::getIdentity() ),
						log_level(Core::LogMessage::LOG_SEVERITY_NONE)
					{}
				};

				/**
				 * @brief Is called when the component is created
				 *
				 * The init stuff must be done in this method. Is called by parent entity after component addition.
				 *
				 */
				virtual void init ( const Core::Entity* parent_entity );

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

				virtual void onTransformChanged ( const Core::TransformChangedMessage &message );
				virtual void doChangeMaterial ( const ChangeMaterialActionMessage &message );

				OgreRenderableComponent ( const std::string &name, const Descriptor &desc, OgreRenderSubsystem* render_system, Core::EngineContext *engine_context );
				virtual ~OgreRenderableComponent();

				virtual void addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message );

			private:
				const Core::ComponentType type;
				OgreRenderSubsystem* render_system;
				OgreRenderableComponentListener* listener;
				OgreMeshPtrProvider* mesh_data_provider;
				Ogre::Entity* entity;
				Ogre::SceneNode* scene_node;
				Core::EngineContext* engine_context;
				Core::MessagingPoliciesManager messaging_policies_manager;

				Descriptor descriptor;

				Core::LogHelper* log_helper;
		};

	} // namespace Graphics
} // namespace UnknownEngine
