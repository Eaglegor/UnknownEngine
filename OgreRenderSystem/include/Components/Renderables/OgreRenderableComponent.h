#pragma once

#include <string>
#include <Objects/Component.h>
#include <Mesh/MeshData.h>
#include <Listeners/OgreRenderableComponentListener.h>
#include <Components/BaseOgreComponent.h>
#include <MessageSystem/MessagingPoliciesManager.h>
#include <ExportedMessages/LogMessage.h>
#include <Exception.h>
#include <AlignedNew.h>

namespace Ogre
{
	class Entity;
	class SceneNode;
}

namespace UnknownEngine
{

	namespace Core
	{
		struct TransformChangedMessage;
		class IMessageListener;
		class EngineContext;
		struct ReceivedMessageDesc;
		class LogHelper;
	}

	namespace Graphics
	{

		class OgreRenderSubsystem;
		class OgreMeshPtrProvider;
		struct ChangeMaterialActionMessage;
		class OgreRenderableComponentListener;

		const Core::ComponentType OGRE_RENDERABLE_COMPONENT_TYPE = "Graphics.Renderable";

		class OgreRenderableComponent: public BaseOgreComponent
		{
			public:

				UNKNOWNENGINE_SIMPLE_EXCEPTION(NoMeshDataProvidedException);
				
				UNKNOWNENGINE_ALIGNED_STRUCT(16) Descriptor
				{
					
					struct MaterialDesc
					{
						std::string name;
						
						MaterialDesc():name("BaseWhiteNoLighting"){};
					};
					
					OgreMeshPtrProvider* mesh_data_provider;
					
					Core::Transform initial_transform;
					Core::LogMessage::Severity log_level;

					MaterialDesc material_desc;
					
					bool throw_exception_on_missing_mesh_data;
					
					UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

					Descriptor() :
						mesh_data_provider ( nullptr ),
						initial_transform ( Core::Transform::getIdentity() ),
						log_level(Core::LogMessage::Severity::LOG_SEVERITY_NONE),
						throw_exception_on_missing_mesh_data(true)
					{}
				};
				
				virtual void start();
				virtual void shutdown();
				virtual Core::ComponentType getType();

				virtual void onTransformChanged ( const Core::TransformChangedMessage &message );
				virtual void doChangeMaterial ( const ChangeMaterialActionMessage &message );

				OgreRenderableComponent ( const std::string &name, const Descriptor &desc, OgreRenderSubsystem* render_system, Core::EngineContext *engine_context );
				virtual ~OgreRenderableComponent();

				virtual void addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message );

				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			protected:
				virtual void internalInit(const Core::Entity* parent_entity);
				
			private:

				Descriptor desc;
				
				OgreRenderableComponentListener* listener;
				
				Ogre::Entity* entity;
				Ogre::SceneNode* scene_node;
		};

	} // namespace Graphics
} // namespace UnknownEngine
