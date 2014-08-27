#include <stdafx.h>

#include <Ogre.h>
#include <Components/Renderables/OgreRenderableComponent.h>
#include <OgreRenderSubsystem.h>
#include <DataProviders/OgreMeshPtrProvider.h>
#include <Listeners/OgreRenderableComponentListener.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <LogHelper.h>
#include <MessageBuffers/OnlyLastMessageBuffer.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderableComponent::OgreRenderableComponent ( const std::string &name, const OgreRenderableComponentDescriptor &desc, OgreRenderSubsystem *render_subsystem, Core::EngineContext *engine_context )
			: BaseOgreComponent ( name, render_subsystem, engine_context ),
			  desc ( desc ),
			  listener ( nullptr )
		{
			if ( desc.log_level > Core::LogMessage::Severity::LOG_SEVERITY_NONE )
			{
				log_helper.reset ( new Core::LogHelper ( getName(), desc.log_level, engine_context ) );
			}

			if ( desc.mesh_data_provider != nullptr ) desc.mesh_data_provider->reserve();

			LOG_INFO ( log_helper, "Logger initialized" );
		}

		OgreRenderableComponent::~OgreRenderableComponent()
		{
			if ( listener != nullptr )
			{

				if ( desc.mesh_data_provider != nullptr ) desc.mesh_data_provider->release();

				LOG_INFO ( log_helper, "Unregistering listener" );
				engine_context->getMessageDispatcher()->removeListener ( listener );
				LOG_INFO ( log_helper, "Deleting listener" );
				delete listener;
			}
		}

		void OgreRenderableComponent::internalInit ( const UnknownEngine::Core::Entity* parent_entity )
		{
			LOG_INFO ( log_helper, "Creating OGRE entity" );
			if ( desc.mesh_data_provider != nullptr )
			{
				Ogre::MeshPtr mesh_data = desc.mesh_data_provider->getResource().getData<Ogre::MeshPtr>();
				entity = render_subsystem->getSceneManager()->createEntity ( getName() + ".OgreEntity", mesh_data );
			}
			else
			{
				if ( desc.throw_exception_on_missing_mesh_data )
				{
					LOG_ERROR ( log_helper, "No mesh data provider found!" );
					throw NoMeshDataProvidedException ( "No mesh data provided to construct renderable component" );
				}
				else
				{
					LOG_ERROR ( log_helper, "No mesh data provider found. Using substitute mesh (Ogre::PT_SPHERE) instead" );
					entity = render_subsystem->getSceneManager()->createEntity ( getName() + ".OgreEntity", Ogre::SceneManager::PT_SPHERE );
				}
			}

			entity->setMaterialName ( desc.material_desc.name );

			LOG_INFO ( log_helper, "Creating OGRE scene node" )
			scene_node = render_subsystem->getSceneManager()->getRootSceneNode()->createChildSceneNode ( getName() + ".SceneNode" );

			scene_node->setPosition ( OgreVector3Converter::toOgreVector ( desc.initial_transform.getPosition() ) );
			scene_node->setOrientation ( OgreQuaternionConverter::toOgreQuaternion ( desc.initial_transform.getOrientation() ) );

			LOG_INFO ( log_helper, "Starting" );
			scene_node->attachObject ( entity );
		}

		void OgreRenderableComponent::internalShutdown()
		{
			LOG_INFO ( log_helper, "Shutting down" );
			scene_node->detachObject ( entity );

			LOG_INFO ( log_helper, "Destroying scene node" );
			render_subsystem->getSceneManager()->destroySceneNode ( scene_node );

			LOG_INFO ( log_helper, "Destroying entity" );
			render_subsystem->getSceneManager()->destroyEntity ( entity );
		}

		Core::ComponentType OgreRenderableComponent::getType()
		{
			return OGRE_RENDERABLE_COMPONENT_TYPE;
		}

		void OgreRenderableComponent::addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message )
		{
			/*if ( listener == nullptr ) listener = new OgreRenderableComponentListener ( getName() + ".Listener", this, engine_context, render_subsystem );
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
			}*/
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

		void OgreRenderableComponent::registerMessageProcessors ( Core::BaseMessageListener* message_listener )
		{
			typedef Utils::OnlyLastMessageBuffer< Core::TransformChangedMessage > TransformChangedMessageBuffer;
			
			std::unique_ptr < TransformChangedMessageBuffer > buffer ( new TransformChangedMessageBuffer ( std::bind ( &OgreRenderableComponent::onTransformChanged, this, std::placeholders::_1 ) ) );
			message_listener->registerMessageBuffer( MESSAGE_TYPE_ID( Core::TransformChangedMessage::getTypeName() ), std::move(buffer) );
		}

		void OgreRenderableComponent::processMessages()
		{
			flushMessages();
		}
		
	} // namespace Graphics
} // namespace UnknownEngine
