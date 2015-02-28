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
#include <mutex>

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

			LOG_INFO ( logger, "Starting" );
			scene_node->attachObject ( entity );
			
			transform_adapter.setTransform(desc.initial_transform);
			
			if(transform_provider)
			{
				transform_provider->addListener(&transform_adapter);
			}
		}

		void OgreRenderableComponent::internalShutdown()
		{
			if(transform_provider)
			{
				transform_provider->removeListener(&transform_adapter);
			}
			
			LOG_INFO ( logger, "Shutting down" );
			scene_node->detachObject ( entity );

			LOG_INFO ( logger, "Destroying scene node" );
			render_subsystem->getSceneManager()->destroySceneNode ( scene_node );

			LOG_INFO ( logger, "Destroying entity" );
			render_subsystem->getSceneManager()->destroyEntity ( entity );
		}

		void OgreRenderableComponent::_update()
		{
			transform_adapter.apply(this);
		}

		void OgreRenderableComponent::setMaterialName ( const char* material_name )
		{
			this->entity->setMaterialName(material_name);
		}
		
		void OgreRenderableComponent::setOrientation ( const Math::Quaternion& quaternion )
		{
			this->scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(quaternion) );
		}

		void OgreRenderableComponent::setPosition ( const Math::Vector3& position )
		{
			this->scene_node->setPosition( OgreVector3Converter::toOgreVector(position) );
		}

		void OgreRenderableComponent::setTransform ( const Math::Transform& transform )
		{
			this->scene_node->setPosition( OgreVector3Converter::toOgreVector(transform.getPosition()) );
			this->scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(transform.getOrientation()) );
		}
		
		Core::IComponentInterface* OgreRenderableComponent::getInterface ( const Core::ComponentType& type )
		{
			using namespace ComponentInterfaces;
			if(type == MovableComponent::getTypeName() ) return static_cast<MovableComponent*>(&transform_adapter);
			if(type == IRenderable::getTypeName() ) return static_cast<IRenderable*>(this);
			return nullptr;
		}
		
	} // namespace Graphics
} // namespace UnknownEngine
