#include <Components/BaseOgreLightComponent.h>
#include <OgreRenderSubsystem.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreColourValueConverter.h>
#include <Listeners/BaseOgreLightComponentListener.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/MessageDispatcher.h>
#include <OgreSceneManager.h>


namespace UnknownEngine
{
	namespace Graphics
	{

		void BaseOgreLightComponent::shutdown()
		{
			ogre_scene_node->detachObject(ogre_light);
		}

		void BaseOgreLightComponent::start()
		{
			ogre_scene_node->attachObject(ogre_light);
		}

		void BaseOgreLightComponent::init ( const UnknownEngine::Core::Entity* parent_entity )
		{
			ogre_light = render_subsystem->getSceneManager()->createLight(getName() + ".Light");
			ogre_scene_node = render_subsystem->getSceneManager()->getRootSceneNode()->createChildSceneNode(getName()+".SceneNode");
			
			Ogre::ColourValue diffuse_color = OgreColourValueConverter::toOgreColourValue( light_settings.diffuse_color ) * light_settings.intensity;
			ogre_light->setDiffuseColour( diffuse_color );
			
			Ogre::ColourValue specular_color = OgreColourValueConverter::toOgreColourValue( light_settings.specular_color ) * light_settings.intensity;
			ogre_light->setDiffuseColour( specular_color );
		}

		BaseOgreLightComponent::BaseOgreLightComponent ( const std::string& name, UnknownEngine::Graphics::OgreRenderSubsystem* render_subsystem, UnknownEngine::Core::EngineContext* engine_context, const UnknownEngine::Graphics::OgreLightSettings& light_settings ):
		Component(name),
		render_subsystem(render_subsystem),
		engine_context(engine_context),
		listener(nullptr),
		messaging_policies_manager(engine_context),
		light_settings(light_settings)
		{
		}
		
		BaseOgreLightComponent::~BaseOgreLightComponent()
		{
			if(listener != nullptr)
			{
				engine_context->getMessageDispatcher()->removeListener(listener);
				delete listener;
			}
			
			render_subsystem->getSceneManager()->destroyLight(ogre_light);
			render_subsystem->getSceneManager()->destroySceneNode(ogre_scene_node);
		}
		
		void BaseOgreLightComponent::onTransformChanged ( const Core::TransformChangedMessage& msg )
		{
			ogre_light->setPosition( OgreVector3Converter::toOgreVector(msg.new_transform.getPosition()) );
		}

		void BaseOgreLightComponent::addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message )
		{
			if ( listener == nullptr )
			{
				listener = new BaseOgreLightComponentListener ( getName() + ".Listener", this );
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
		
		void BaseOgreLightComponent::setLogHelper ( Core::LogHelper* log_helper )
		{
			this->log_helper = log_helper;
		}
		
	}
}
