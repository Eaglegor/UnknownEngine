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
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		void OgreRenderableComponent::init ( const Core::Entity *parent_entity )
		{
			LOG_INFO ( log_helper, "Creating OGRE entity" );
			entity = render_system->getSceneManager()->createEntity ( getName() + ".Entity", Ogre::SceneManager::PT_SPHERE /*mesh_data_provider->getResource().getData<Ogre::MeshPtr>()*/ );

			entity->setMaterialName ( descriptor.material_name );

			LOG_INFO ( log_helper, "Creating OGRE scene node" )
			scene_node = render_system->getSceneManager()->getRootSceneNode()->createChildSceneNode ( getName() + ".SceneNode" );

			scene_node->setPosition ( OgreVector3Converter::toOgreVector(descriptor.initial_transform.getPosition()) );
		}

		void OgreRenderableComponent::start()
		{
			LOG_INFO ( log_helper, "Starting" );
			scene_node->attachObject ( entity );
		}

		void OgreRenderableComponent::shutdown()
		{
			LOG_INFO ( log_helper, "Shutting down" );
			scene_node->detachObject ( entity );
		}

		Core::ComponentType OgreRenderableComponent::getType()
		{
			return type;
		}

		void OgreRenderableComponent::onTransformChanged ( const Core::TransformChangedMessage &message )
		{
			this->scene_node->setPosition ( OgreVector3Converter::toOgreVector ( message.new_transform.getPosition() ) );
			this->scene_node->setOrientation ( OgreQuaternionConverter::toOgreQuaternion ( message.new_transform.getOrientation() ) );
		}

		void OgreRenderableComponent::doChangeMaterial ( const ChangeMaterialActionMessage &message )
		{
			this->entity->setMaterialName ( message.new_material_name );
		}

		OgreRenderableComponent::OgreRenderableComponent ( const std::string &name, const Descriptor &desc, OgreRenderSubsystem *render_system, Core::EngineContext *engine_context )
			: Core::Component ( name ),
			  render_system ( render_system ),
			  type ( OGRE_RENDERABLE_COMPONENT_TYPE ),
			  descriptor ( desc ),
			  listener ( nullptr ),
			  engine_context ( engine_context ),
			  messaging_policies_manager ( engine_context )
		{
			log_helper = new Core::LogHelper ( getName(), Core::LogMessage::LOG_SEVERITY_INFO, engine_context );
			LOG_INFO ( log_helper, "Logger initialized" );
		}

		OgreRenderableComponent::~OgreRenderableComponent()
		{
			if ( listener != nullptr )
			{
				LOG_INFO ( log_helper, "Unregistering listener" );
				engine_context->getMessageDispatcher()->removeListener ( listener );
				LOG_INFO ( log_helper, "Deleting listener" );
				delete listener;
			}

			//mesh_data_provider->release();

			LOG_INFO ( log_helper, "Destroying scene node" );
			render_system->getSceneManager()->destroySceneNode ( scene_node );

			LOG_INFO ( log_helper, "Destroying entity" );
			render_system->getSceneManager()->destroyEntity ( entity );

			if ( log_helper ) delete log_helper;
		}

		void OgreRenderableComponent::addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message )
		{
			if ( listener == nullptr ) listener = new OgreRenderableComponentListener ( getName() + ".Listener", this, engine_context );
			if ( listener->supportsMessageTypeName ( received_message.message_type_name ) )
			{
				engine_context->getMessageDispatcher()->addListener (
				    received_message.message_type_name, listener,
				    messaging_policies_manager.createPrefabReceiveMessagePolicy ( received_message.receive_policy_type_name, received_message.receive_policy_options )
				);
			}
			else
			{
				throw Core::IMessageListener::MessageTypeNotSupportedByListener ( "Listener of component " + getName() + " doesn't support message type " + received_message.message_type_name );
			}
		}

	} // namespace Graphics
} // namespace UnknownEngine
