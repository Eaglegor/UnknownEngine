#include <Components/OgrePointLightComponent.h>
#include <OgreRenderSubsystem.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreColourValueConverter.h>
#include <Listeners/OgrePointLightComponentListener.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/MessageDispatcher.h>
#include <OgreSceneManager.h>


namespace UnknownEngine
{
	namespace Graphics
	{

		UnknownEngine::Core::ComponentType OgrePointLightComponent::getType()
		{
			return OGRE_POINT_LIGHT_COMPONENT_TYPE;
		}

		void OgrePointLightComponent::shutdown()
		{
			ogre_scene_node->detachObject(ogre_light);
		}

		void OgrePointLightComponent::start()
		{
			ogre_scene_node->attachObject(ogre_light);
		}

		void OgrePointLightComponent::init ( const UnknownEngine::Core::Entity* parent_entity )
		{
			ogre_light = render_subsystem->getSceneManager()->createLight(getName() + ".Light");
			ogre_scene_node = render_subsystem->getSceneManager()->getRootSceneNode()->createChildSceneNode(getName()+".SceneNode");
			
			Ogre::ColourValue color = OgreColourValueConverter::toOgreColourValue( desc.color );
			if(desc.intensity.is_initialized()) color *= desc.intensity.get();
			
			ogre_light->setDiffuseColour(color);
			
			ogre_scene_node->setPosition( OgreVector3Converter::toOgreVector(desc.initial_transform.getPosition()) );
		}

		OgrePointLightComponent::OgrePointLightComponent ( const std::string& name, const UnknownEngine::Graphics::OgrePointLightComponent::Descriptor& desc, UnknownEngine::Graphics::OgreRenderSubsystem* render_subsystem, UnknownEngine::Core::EngineContext* engine_context ):
		Component(name),
		render_subsystem(render_subsystem),
		engine_context(engine_context),
		desc(desc),
		listener(nullptr),
		messaging_policies_manager(engine_context)
		{
		}
		
		OgrePointLightComponent::~OgrePointLightComponent()
		{
			if(listener != nullptr)
			{
				engine_context->getMessageDispatcher()->removeListener(listener);
				delete listener;
			}
			
			render_subsystem->getSceneManager()->destroyLight(ogre_light);
			render_subsystem->getSceneManager()->destroySceneNode(ogre_scene_node);
		}
		
		void OgrePointLightComponent::onTransformChanged ( const Core::TransformChangedMessage& msg )
		{
			ogre_light->setPosition( OgreVector3Converter::toOgreVector(msg.new_transform.getPosition()) );
		}

		void OgrePointLightComponent::addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message )
		{
			if ( listener == nullptr )
			{
				listener = new OgrePointLightComponentListener ( getName() + ".Listener", this );
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
		
	}
}
