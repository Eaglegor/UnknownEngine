#include <stdafx.h>

#include <Components/Cameras/OgreCameraComponent.h>
#include <OgreRenderSubsystem.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <boost/lexical_cast.hpp>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>

#include <LogHelper.h>
#include <Listeners/BaseMessageListenerBufferRegistrator.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <MessageBuffers/OnlyLastMessageBuffer.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <ExportedMessages/RenderSystem/CameraLookAtActionMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{


		OgreCameraComponent::OgreCameraComponent ( const std::string &name, const OgreCameraComponentDescriptor &desc, OgreRenderSubsystem *render_subsystem, Core::EngineContext *engine_context )
			: BaseOgreComponent ( name, render_subsystem, engine_context ),
			  desc ( desc )
		{
			if ( desc.log_level > Core::LogMessage::Severity::LOG_SEVERITY_NONE )
			{
				log_helper.reset ( new Core::LogHelper ( getName(), desc.log_level, engine_context ) );
			}

			LOG_INFO ( log_helper, "Logger initialized" );
		}

		OgreCameraComponent::~OgreCameraComponent()
		{
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
			this->camera = render_subsystem->getSceneManager()->createCamera ( Ogre::String ( getName() ) + ".Camera" );

			LOG_INFO ( log_helper, "Creating OGRE scene node" );
			this->scene_node = render_subsystem->getSceneManager()->getRootSceneNode()->createChildSceneNode ( Ogre::String ( getName() ) + ".SceneNode" );

			Ogre::RenderWindow* render_window = render_subsystem->getRenderWindow(desc.render_window_name);
			if(!render_window) throw RenderWindowNotFound("Can't find render window " + desc.render_window_name + " to create viewport for camera " + std::string(getName()));
			render_window->addViewport ( camera );

			scene_node->setPosition ( OgreVector3Converter::toOgreVector ( desc.initial_transform.getPosition() ) );
			scene_node->setOrientation ( OgreQuaternionConverter::toOgreQuaternion ( desc.initial_transform.getOrientation() ) );

			if ( desc.initial_look_at.is_initialized() )
			{
				LOG_DEBUG ( log_helper, "Setting look at: " +
				            boost::lexical_cast<std::string> ( desc.initial_look_at->x() ) + ", " +
				            boost::lexical_cast<std::string> ( desc.initial_look_at->y() ) + ", " +
				            boost::lexical_cast<std::string> ( desc.initial_look_at->z() ) );

				camera->lookAt ( OgreVector3Converter::toOgreVector ( desc.initial_look_at.get() ) );
			}

			if ( desc.near_clip_distance.is_initialized() ) camera->setNearClipDistance ( desc.near_clip_distance.get() );
			if ( desc.far_clip_distance.is_initialized() ) camera->setFarClipDistance ( desc.far_clip_distance.get() );

			this->scene_node->attachObject ( this->camera );
			
			if(listener) listener->registerAtDispatcher();
		}

		void OgreCameraComponent::internalShutdown()
		{
			if(listener) listener->unregisterAtDispatcher();
			
			LOG_INFO ( log_helper, "Shutting down" );
			this->scene_node->detachObject ( this->camera );
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

		void OgreCameraComponent::initMessageListenerBuffers ( bool can_be_multi_threaded )
		{
			if ( !listener ) return;

			Utils::BaseMessageListenerBufferRegistrator<OgreCameraComponent> registrator ( listener.get(), this );

			if ( can_be_multi_threaded )
			{
				registrator.registerStandardMessageBuffer <
				Core::TransformChangedMessage,
				Utils::OnlyLastMessageBuffer<Core::TransformChangedMessage>
				> ( &OgreCameraComponent::onTransformChanged );
				
				registrator.registerStandardMessageBuffer <
				CameraLookAtActionMessage,
				Utils::OnlyLastMessageBuffer<CameraLookAtActionMessage>
				> ( &OgreCameraComponent::doLookAt );
			}
			else
			{
				registrator.registerStandardMessageBuffer <
				Core::TransformChangedMessage,
				Utils::InstantForwardMessageBuffer<Core::TransformChangedMessage>
				> ( &OgreCameraComponent::onTransformChanged );
				
				registrator.registerStandardMessageBuffer <
				CameraLookAtActionMessage,
				Utils::InstantForwardMessageBuffer<CameraLookAtActionMessage>
				> ( &OgreCameraComponent::doLookAt );
			}
		}

	}
}
