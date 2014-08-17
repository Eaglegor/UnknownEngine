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

namespace UnknownEngine
{
	namespace Graphics
	{

		void OgreRenderableComponent::init ( const Core::Entity *parent_entity )
		{
			LOG_INFO ( log_helper, "Creating OGRE entity" );
			if(desc.mesh_data_provider!=nullptr)
			{
				entity = render_system->getSceneManager()->createEntity ( getName() + ".OgreEntity", desc.mesh_data_provider->getResource().getData<Ogre::MeshPtr>() );
			}
			else
			{
				if(desc.throw_exception_on_missing_mesh_data){
					LOG_ERROR( log_helper, "No mesh data provider found!" );
					throw NoMeshDataProvidedException("No mesh data provided to construct renderable component");
				}
				else
				{
					LOG_ERROR ( log_helper, "No mesh data provider found. Using substitute mesh (Ogre::PT_SPHERE) instead");
					entity = render_system->getSceneManager()->createEntity ( getName() + ".OgreEntity", Ogre::SceneManager::PT_SPHERE );
				}
			}

			entity->setMaterialName ( desc.material_desc.name );

			LOG_INFO ( log_helper, "Creating OGRE scene node" )
			scene_node = render_system->getSceneManager()->getRootSceneNode()->createChildSceneNode ( getName() + ".SceneNode" );

			scene_node->setPosition ( OgreVector3Converter::toOgreVector(desc.initial_transform.getPosition()) );
			scene_node->setOrientation ( OgreQuaternionConverter::toOgreQuaternion(desc.initial_transform.getOrientation()) );
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
			  desc ( desc ),
			  listener ( nullptr ),
			  engine_context ( engine_context ),
			  messaging_policies_manager ( engine_context ),
			  log_helper(nullptr)
		{
			if(desc.log_level > Core::LogMessage::Severity::LOG_SEVERITY_NONE)
			{
				log_helper = new Core::LogHelper ( getName(), desc.log_level, engine_context );
			}
			
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

			if(desc.mesh_data_provider != nullptr) desc.mesh_data_provider->release();
			
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
