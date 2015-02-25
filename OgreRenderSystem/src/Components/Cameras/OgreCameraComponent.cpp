#include <stdafx.h>

#include <Components/Cameras/OgreCameraComponent.h>
#include <OgreRenderSubsystem.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreSceneNode.h>
#include <boost/lexical_cast.hpp>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/BaseMessageListener.h>

#include <Logging.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <MessageBuffers/OnlyLastMessageBuffer.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <ExportedMessages/RenderSystem/CameraLookAtActionMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{


		OgreCameraComponent::OgreCameraComponent ( const std::string &name, const OgreCameraComponentDescriptor &desc, OgreRenderSubsystem *render_subsystem )
			: BaseOgreComponent ( name, render_subsystem ),
			  desc ( desc ),
			  logger(name, desc.log_level),
			  scene_node(nullptr),
			  camera(nullptr),
			  render_window(desc.render_window),
			  transform_provider(desc.transform_provider)
		{
			LOG_INFO ( logger, "Logger initialized" );
		}

		OgreCameraComponent::~OgreCameraComponent()
		{
			LOG_INFO ( logger, "Destroying OGRE camera" );
			render_subsystem->getSceneManager()->destroyCamera ( this->camera );

			LOG_INFO ( logger, "Destroying OGRE scene node" );
			render_subsystem->getSceneManager()->destroySceneNode ( this->scene_node );
		}

		void OgreCameraComponent::internalInit (  )
		{
			if(!render_window) {
				LOG_ERROR(logger, "Can't find render window to create camera viewport");
				return;
			}
			
			LOG_INFO ( logger, "Creating OGRE camera" );
			this->camera = render_subsystem->getSceneManager()->createCamera ( Ogre::String ( getName() ) + ".Camera" );

			LOG_INFO ( logger, "Creating OGRE scene node" );
			this->scene_node = render_subsystem->getSceneManager()->getRootSceneNode()->createChildSceneNode ( Ogre::String ( getName() ) + ".SceneNode" );

			render_window->getOgreRenderWindow()->addViewport ( camera );

			scene_node->setPosition ( OgreVector3Converter::toOgreVector ( desc.initial_transform.getPosition() ) );
			scene_node->setOrientation ( OgreQuaternionConverter::toOgreQuaternion ( desc.initial_transform.getOrientation() ) );

			if ( desc.initial_look_at.is_initialized() )
			{
				LOG_DEBUG ( logger, "Setting look at: " +
				            boost::lexical_cast<std::string> ( desc.initial_look_at->x() ) + ", " +
				            boost::lexical_cast<std::string> ( desc.initial_look_at->y() ) + ", " +
				            boost::lexical_cast<std::string> ( desc.initial_look_at->z() ) );

				camera->lookAt ( OgreVector3Converter::toOgreVector ( desc.initial_look_at.get() ) );
			}

			if ( desc.near_clip_distance.is_initialized() ) camera->setNearClipDistance ( desc.near_clip_distance.get() );
			if ( desc.far_clip_distance.is_initialized() ) camera->setFarClipDistance ( desc.far_clip_distance.get() );

			this->scene_node->attachObject ( this->camera );
		}

		void OgreCameraComponent::internalShutdown()
		{
			LOG_INFO ( logger, "Shutting down" );
			if(scene_node && camera) this->scene_node->detachObject ( this->camera );
		}

		void OgreCameraComponent::_update()
		{
			if(transform_provider) 
			{
				this->scene_node->setPosition ( OgreVector3Converter::toOgreVector ( transform_provider->getPosition() ) );
				this->scene_node->setOrientation ( OgreQuaternionConverter::toOgreQuaternion ( transform_provider->getOrientation() ) );
			}
		}
		
		void OgreCameraComponent::doLookAt ( const CameraLookAtActionMessage &msg )
		{
			camera->lookAt ( OgreVector3Converter::toOgreVector ( msg.look_at_position ) );
		}

	}
}
