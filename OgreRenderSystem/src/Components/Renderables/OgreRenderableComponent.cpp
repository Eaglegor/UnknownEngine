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
#include <Logging.h>
#include <MessageBuffers/OnlyLastMessageBuffer.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
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
			logger = CREATE_LOGGER(getName(), desc.log_level);

			if ( desc.mesh_data_provider != nullptr ) desc.mesh_data_provider->reserve();

			LOG_INFO ( logger, "Logger initialized" );
		}

		OgreRenderableComponent::~OgreRenderableComponent()
		{
			if ( desc.mesh_data_provider != nullptr ) desc.mesh_data_provider->release();
			RELEASE_LOGGER(logger);
		}

		void OgreRenderableComponent::internalInit ( const UnknownEngine::Core::Entity* parent_entity )
		{
			LOG_INFO ( logger, "Creating OGRE entity" );
			if ( desc.mesh_data_provider != nullptr )
			{
				Ogre::MeshPtr mesh_data = desc.mesh_data_provider->getResource().getData<Ogre::MeshPtr>();
				entity = render_subsystem->getSceneManager()->createEntity ( Ogre::String(getName()) + ".OgreEntity", mesh_data );
			}
			else
			{
				if ( desc.throw_exception_on_missing_mesh_data )
				{
					LOG_ERROR ( logger, "No mesh data provider found!" );
					throw NoMeshDataProvidedException ( "No mesh data provided to construct renderable component" );
				}
				else
				{
					LOG_ERROR ( logger, "No mesh data provider found. Using substitute mesh (Ogre::PT_SPHERE) instead" );
					entity = render_subsystem->getSceneManager()->createEntity ( Ogre::String(getName()) + ".OgreEntity", Ogre::SceneManager::PT_SPHERE );
				}
			}

			entity->setMaterialName ( desc.material_desc.name );

			LOG_INFO ( logger, "Creating OGRE scene node" );
			scene_node = render_subsystem->getSceneManager()->getRootSceneNode()->createChildSceneNode ( Ogre::String(getName()) + ".SceneNode" );

			scene_node->setPosition ( OgreVector3Converter::toOgreVector ( desc.initial_transform.getPosition() ) );
			scene_node->setOrientation ( OgreQuaternionConverter::toOgreQuaternion ( desc.initial_transform.getOrientation() ) );

			LOG_INFO ( logger, "Starting" );
			scene_node->attachObject ( entity );
			
			LOG_INFO (logger, "Registering listener");
			if(listener && !listener->isRegisteredAtDispatcher()) listener->registerAtDispatcher();
		}

		void OgreRenderableComponent::internalShutdown()
		{
			LOG_INFO (logger, "Unregistering listener");
			if(listener) listener->unregisterAtDispatcher();
			
			LOG_INFO ( logger, "Shutting down" );
			scene_node->detachObject ( entity );

			LOG_INFO ( logger, "Destroying scene node" );
			render_subsystem->getSceneManager()->destroySceneNode ( scene_node );

			LOG_INFO ( logger, "Destroying entity" );
			render_subsystem->getSceneManager()->destroyEntity ( entity );
		}

		Core::ComponentType OgreRenderableComponent::getType() const
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
			
			if(can_be_multi_threaded)
			{
				{
					typedef Core::TransformChangedMessage MessageType;
					typedef Utils::OnlyLastMessageBuffer<MessageType> BufferType;

					listener->createMessageBuffer<MessageType, BufferType>(this, &OgreRenderableComponent::onTransformChanged);
				}

				{
					typedef ChangeMaterialActionMessage MessageType;
					typedef Utils::OnlyLastMessageBuffer<MessageType> BufferType;

					listener->createMessageBuffer<MessageType, BufferType>(this, &OgreRenderableComponent::doChangeMaterial);
				}
			
				listener->registerAtDispatcher();
			
			}
			else
			{
				{
					typedef Core::TransformChangedMessage MessageType;
					typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;

					listener->createMessageBuffer<MessageType, BufferType>(this, &OgreRenderableComponent::onTransformChanged);
				}

				{
					typedef ChangeMaterialActionMessage MessageType;
					typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;

					listener->createMessageBuffer<MessageType, BufferType>(this, &OgreRenderableComponent::doChangeMaterial);
				}
			}
		}
		
	} // namespace Graphics
} // namespace UnknownEngine
