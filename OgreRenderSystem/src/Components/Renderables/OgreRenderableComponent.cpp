#include <stdafx.h>

#include <Ogre.h>
#include <Components/Renderables/OgreRenderableComponent.h>
#include <OgreRenderSubsystem.h>
#include <DataProviders/OgreMeshPtrProvider.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <MessageSystem/BaseMessageListener.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <LogHelper.h>
#include <MessageBuffers/OnlyLastMessageBuffer.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <Listeners/BaseMessageListenerBufferRegistrator.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <ExportedMessages/RenderSystem/ChangeMaterialActionMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderableComponent::OgreRenderableComponent ( const std::string &name, const OgreRenderableComponentDescriptor &desc, OgreRenderSubsystem *render_subsystem, Core::EngineContext *engine_context )
			: BaseOgreComponent ( name, render_subsystem, engine_context ),
			  desc ( desc )
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
			if ( desc.mesh_data_provider != nullptr ) desc.mesh_data_provider->release();
		}

		void OgreRenderableComponent::internalInit ( const UnknownEngine::Core::Entity* parent_entity )
		{
			LOG_INFO ( log_helper, "Creating OGRE entity" );
			if ( desc.mesh_data_provider != nullptr )
			{
				Ogre::MeshPtr mesh_data = desc.mesh_data_provider->getResource().getData<Ogre::MeshPtr>();
				entity = render_subsystem->getSceneManager()->createEntity ( Ogre::String(getName()) + ".OgreEntity", mesh_data );
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
					entity = render_subsystem->getSceneManager()->createEntity ( Ogre::String(getName()) + ".OgreEntity", Ogre::SceneManager::PT_SPHERE );
				}
			}

			entity->setMaterialName ( desc.material_desc.name );

			LOG_INFO ( log_helper, "Creating OGRE scene node" )
			scene_node = render_subsystem->getSceneManager()->getRootSceneNode()->createChildSceneNode ( Ogre::String(getName()) + ".SceneNode" );

			scene_node->setPosition ( OgreVector3Converter::toOgreVector ( desc.initial_transform.getPosition() ) );
			scene_node->setOrientation ( OgreQuaternionConverter::toOgreQuaternion ( desc.initial_transform.getOrientation() ) );

			LOG_INFO ( log_helper, "Starting" );
			scene_node->attachObject ( entity );
			
			LOG_INFO (log_helper, "Registering listener");
			if(listener) listener->registerAtDispatcher();
		}

		void OgreRenderableComponent::internalShutdown()
		{
			LOG_INFO (log_helper, "Unregistering listener");
			if(listener) listener->unregisterAtDispatcher();
			
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

		void OgreRenderableComponent::onTransformChanged ( const Core::TransformChangedMessage &message )
		{
			this->scene_node->setPosition ( OgreVector3Converter::toOgreVector ( message.new_transform.getPosition() ) );
			this->scene_node->setOrientation ( OgreQuaternionConverter::toOgreQuaternion ( message.new_transform.getOrientation() ) );
		}

		void OgreRenderableComponent::doChangeMaterial ( const ChangeMaterialActionMessage &message )
		{
			this->entity->setMaterialName ( message.new_material_name );
		}

		void OgreRenderableComponent::initMessageListenerBuffers ( bool can_be_multi_threaded )
		{
			if(!listener) return;
			
			Utils::BaseMessageListenerBufferRegistrator<OgreRenderableComponent> registrator(listener.get(), this);
			
			if(can_be_multi_threaded)
			{
				registrator.registerStandardMessageBuffer<
				Core::TransformChangedMessage, 
				Utils::OnlyLastMessageBuffer<Core::TransformChangedMessage>
				>( &OgreRenderableComponent::onTransformChanged );
				
				registrator.registerStandardMessageBuffer<
				ChangeMaterialActionMessage, 
				Utils::OnlyLastMessageBuffer<ChangeMaterialActionMessage>
				>( &OgreRenderableComponent::doChangeMaterial );
			}
			else
			{
				registrator.registerStandardMessageBuffer<
				Core::TransformChangedMessage, 
				Utils::InstantForwardMessageBuffer<Core::TransformChangedMessage>
				>( &OgreRenderableComponent::onTransformChanged );
				
				registrator.registerStandardMessageBuffer<
				ChangeMaterialActionMessage, 
				Utils::InstantForwardMessageBuffer<ChangeMaterialActionMessage>
				>( &OgreRenderableComponent::doChangeMaterial );
			}
		}
		
	} // namespace Graphics
} // namespace UnknownEngine