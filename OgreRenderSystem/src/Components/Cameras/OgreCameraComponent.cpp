#include <stdafx.h>

#include <Components/Cameras/OgreCameraComponent.h>
#include <OgreRenderSubsystem.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <boost/lexical_cast.hpp>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <Listeners/OgreCameraComponentListener.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>

#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		
		OgreCameraComponent::OgreCameraComponent ( const std::string &name, const OgreCameraComponentDescriptor &desc, OgreRenderSubsystem *render_subsystem, Core::EngineContext *engine_context )
			: BaseOgreComponent(name, render_subsystem, engine_context),
			  listener ( nullptr ),
			  desc(desc)
		{
			if(desc.log_level > Core::LogMessage::Severity::LOG_SEVERITY_NONE)
			{
				log_helper.reset(new Core::LogHelper ( getName(), desc.log_level, engine_context ));
			}
			
			LOG_INFO ( log_helper, "Logger initialized" );
		}

		OgreCameraComponent::~OgreCameraComponent()
		{

			if ( listener != nullptr )
			{
				LOG_INFO ( log_helper, "Unregistering listener" );
				engine_context->getMessageDispatcher()->removeListener ( listener );
				delete listener;
			}

			LOG_INFO ( log_helper, "Destroying OGRE camera" );
			render_subsystem->getSceneManager()->destroyCamera ( this->camera );

			LOG_INFO ( log_helper, "Destroying OGRE scene node" );
			render_subsystem->getSceneManager()->destroySceneNode ( this->scene_node );
		}
		
		UnknownEngine::Core::ComponentType OgreCameraComponent::getType()
		{
			return OGRE_CAMERA_COMPONENT_TYPE;
		}

		
		void OgreCameraComponent::internalInit ( const UnknownEngine::Core::Entity *parent_entity )
		{
			LOG_INFO ( log_helper, "Creating OGRE camera" );
			this->camera = render_subsystem->getSceneManager()->createCamera ( getName() + ".Camera" );

			LOG_INFO ( log_helper, "Creating OGRE scene node" );
			this->scene_node = render_subsystem->getSceneManager()->getRootSceneNode()->createChildSceneNode ( getName() + ".SceneNode" );

			render_subsystem->getRenderWindow()->addViewport ( camera );

			scene_node->setPosition ( OgreVector3Converter::toOgreVector(desc.initial_transform.getPosition()) );
			scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(desc.initial_transform.getOrientation()) );
			
			if(desc.initial_look_at.is_initialized()) 
			{
				LOG_DEBUG (log_helper, "Setting look at: " +
				boost::lexical_cast<std::string>(desc.initial_look_at->x()) + ", " +
				boost::lexical_cast<std::string>(desc.initial_look_at->y()) + ", " +
				boost::lexical_cast<std::string>(desc.initial_look_at->z()));
				
				camera->lookAt( OgreVector3Converter::toOgreVector(desc.initial_look_at.get()) );
			}
			
			if(desc.near_clip_distance.is_initialized()) camera->setNearClipDistance(desc.near_clip_distance.get());
			if(desc.far_clip_distance.is_initialized()) camera->setFarClipDistance(desc.far_clip_distance.get());
			
			this->scene_node->attachObject ( this->camera );
		}
		
		void OgreCameraComponent::internalShutdown()
		{
			LOG_INFO ( log_helper, "Shutting down" );
			this->scene_node->detachObject ( this->camera );
		}
		
		void OgreCameraComponent::addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message )
		{
			if ( listener == nullptr )
			{
				listener = new OgreCameraComponentListener ( getName() + ".Listener", this, engine_context, render_subsystem );
			}

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
		
		void OgreCameraComponent::onTransformChanged ( const Core::TransformChangedMessage &msg )
		{
			this->scene_node->setPosition ( OgreVector3Converter::toOgreVector ( msg.new_transform.getPosition() ) );
			this->scene_node->setOrientation ( OgreQuaternionConverter::toOgreQuaternion ( msg.new_transform.getOrientation() ) );
		}

		void OgreCameraComponent::doLookAt ( const CameraLookAtActionMessage &msg )
		{
			camera->lookAt ( OgreVector3Converter::toOgreVector ( msg.look_at_position ) );
		}

	}
}
