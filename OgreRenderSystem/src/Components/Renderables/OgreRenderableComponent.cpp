#include <stdafx.h>

#include <Ogre.h>
#include <Components/Renderables/OgreRenderableComponent.h>
#include <OgreRenderSubsystem.h>
#include <DataProviders/OgreMeshPtrProvider.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/BaseMessageListener.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <Logging.h>
#include <MessageBuffers/OnlyLastMessageBuffer.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <ExportedMessages/RenderSystem/ChangeMaterialActionMessage.h>
#include <ResourceManager/ResourceManager.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderableComponent::OgreRenderableComponent ( const std::string &name, const OgreRenderableComponentDescriptor &desc, OgreRenderSubsystem *render_subsystem)
			: BaseOgreComponent ( name, render_subsystem ),
			  transform_provider(desc.transform_provider),
			  desc ( desc ),
			  logger(name.c_str(), desc.log_level)
		{
			if ( desc.mesh_data_provider != nullptr ) 
			{
				GET_DATA_PROVIDER(desc.mesh_data_provider->getName());
			}

			LOG_INFO ( logger, "Logger initialized" );
		}

		OgreRenderableComponent::~OgreRenderableComponent()
		{
			if ( desc.mesh_data_provider != nullptr ) 
			{
				LOG_INFO(logger, "Releasing ogre mesh data provider");
				RELEASE_DATA_PROVIDER(desc.mesh_data_provider);
			}
		}

		void OgreRenderableComponent::internalInit ()
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
			
			//LOG_INFO (logger, "Registering listener");
			//if(listener && !listener->isRegisteredAtDispatcher()) listener->registerAtDispatcher();
		}

		void OgreRenderableComponent::internalShutdown()
		{
			//LOG_INFO (logger, "Unregistering listener");
			//if(listener) listener->unregisterAtDispatcher();
			
			LOG_INFO ( logger, "Shutting down" );
			scene_node->detachObject ( entity );

			LOG_INFO ( logger, "Destroying scene node" );
			render_subsystem->getSceneManager()->destroySceneNode ( scene_node );

			LOG_INFO ( logger, "Destroying entity" );
			render_subsystem->getSceneManager()->destroyEntity ( entity );
		}

		void OgreRenderableComponent::_update()
		{
			if(transform_provider)
			{
				this->scene_node->setPosition ( OgreVector3Converter::toOgreVector(transform_provider->getPosition()) );
				this->scene_node->setOrientation ( OgreQuaternionConverter::toOgreQuaternion(transform_provider->getOrientation()) );
			}
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
		
	} // namespace Graphics
} // namespace UnknownEngine
