#include <stdafx.h>

#include <Ogre.h>
#include <Components/OgreRenderableComponent.h>
#include <OgreRenderSubsystem.h>
#include <DataProviders/OgreMeshPtrProvider.h>
#include <Listeners/OgreRenderableComponentListener.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>

namespace UnknownEngine {
	namespace Graphics {

		void OgreRenderableComponent::init(const Core::Entity *parent_entity)
		{
			entity = render_system->getSceneManager()->createEntity(getName()+".Entity", mesh_data_provider->getResource().getData<Ogre::MeshPtr>());
			scene_node = render_system->getSceneManager()->getRootSceneNode()->createChildSceneNode(getName()+".SceneNode");
		}

		void OgreRenderableComponent::start()
		{
			scene_node->attachObject(entity);
		}

		void OgreRenderableComponent::shutdown()
		{
			scene_node->detachObject(entity);
		}

		Core::ComponentType OgreRenderableComponent::getType()
		{
			return type;
		}

		void OgreRenderableComponent::onTransformChanged(const Core::TransformChangedMessage &message)
		{
		  this->scene_node->setPosition( OgreVector3Converter::toOgreVector(message.new_transform.getPosition()) );
		  this->scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(message.new_transform.getOrientation()) );
		}

		void OgreRenderableComponent::doChangeMaterial(const ChangeMaterialActionMessage &message)
		{
		  this->entity->setMaterialName(message.new_material_name);
		}

		OgreRenderableComponent::OgreRenderableComponent(const std::string &name, const Descriptor &desc, OgreRenderSubsystem *render_system, Core::EngineContext *engine_context)
			: Core::Component(name),
			  render_system(render_system),
			  type(OGRE_RENDERABLE_COMPONENT_TYPE),
			  mesh_data_provider(desc.mesh_data_provider),
			  listener(nullptr),
			  engine_context(engine_context),
			  messaging_policies_manager(engine_context)
		{
		}

		OgreRenderableComponent::~OgreRenderableComponent()
		{
			if(listener != nullptr)
			{
				engine_context->getMessageDispatcher()->removeListener(listener);
				delete listener;
			}
			mesh_data_provider->release();
			render_system->getSceneManager()->destroySceneNode(scene_node);
			render_system->getSceneManager()->destroyEntity(entity);
		}

		void OgreRenderableComponent::addReceivedMessageType(const Core::ReceivedMessageDesc &received_message)
		{
			if(listener==nullptr) listener = new OgreRenderableComponentListener(getName()+".Listener", this, engine_context);
			if(listener->supportsMessageTypeName(received_message.message_type_name))
			{
				engine_context->getMessageDispatcher()->addListener(
							received_message.message_type_name, listener,
							messaging_policies_manager.createPrefabReceiveMessagePolicy(received_message.receive_policy_type_name, received_message.receive_policy_options)
							);
			}
			else
			{
				throw Core::IMessageListener::MessageTypeNotSupportedByListener("Listener of component " + getName() + " doesn't support message type " + received_message.message_type_name);
			}
		}

	} // namespace Graphics
} // namespace UnknownEngine
