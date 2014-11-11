#include <stdafx.h>

#include <Components/Lights/BaseOgreLightComponent.h>
#include <OgreRenderSubsystem.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreColourValueConverter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <MessageBuffers/OnlyLastMessageBuffer.h>
#include <MessageSystem/BaseMessageListener.h>
#include <MessageSystem/MessageDispatcher.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>


namespace UnknownEngine
{
	namespace Graphics
	{

		BaseOgreLightComponent::BaseOgreLightComponent ( const std::string& name, UnknownEngine::Graphics::OgreRenderSubsystem* render_subsystem, UnknownEngine::Core::EngineContext* engine_context, const UnknownEngine::Graphics::OgreLightSettings& light_settings ):
		BaseOgreComponent(name, render_subsystem, engine_context),
		light_settings(light_settings)
		{
		}
		
		BaseOgreLightComponent::~BaseOgreLightComponent()
		{
		}
		
		void BaseOgreLightComponent::internalInit( const UnknownEngine::Core::Entity* parent_entity )
		{
			ogre_light = render_subsystem->getSceneManager()->createLight(Ogre::String(getName()) + ".Light");
			ogre_scene_node = render_subsystem->getSceneManager()->getRootSceneNode()->createChildSceneNode(Ogre::String(getName())+".SceneNode");
			
			Ogre::ColourValue diffuse_color = light_settings.diffuse_color * light_settings.intensity;
			ogre_light->setDiffuseColour( diffuse_color );
			
			Ogre::ColourValue specular_color = light_settings.specular_color * light_settings.intensity;
			ogre_light->setSpecularColour( specular_color );
			
			if(light_settings.attenuation.is_initialized())
			{
				const OgreLightSettings::Attenuation& att = light_settings.attenuation.get();
				ogre_light->setAttenuation(att.range, att.constant, att.linear, att.quadratic);
			}
			
			if(light_settings.cast_shadows.is_initialized())
			{
				ogre_light->setCastShadows(light_settings.cast_shadows.get());
			}
			
			ogre_scene_node->attachObject(ogre_light);
			
			if(listener) listener->registerAtDispatcher();
		}
		
		void BaseOgreLightComponent::internalShutdown()
		{
			if(listener) listener->unregisterAtDispatcher();
			
			ogre_scene_node->detachObject(ogre_light);
			
			render_subsystem->getSceneManager()->destroyLight(ogre_light);
			render_subsystem->getSceneManager()->destroySceneNode(ogre_scene_node);
		}
		
		void BaseOgreLightComponent::onTransformChanged ( const Core::TransformChangedMessage& msg )
		{
			ogre_scene_node->setPosition( OgreVector3Converter::toOgreVector(msg.new_transform.getPosition()) );
			ogre_scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(msg.new_transform.getOrientation()) );
		}
		
		void BaseOgreLightComponent::initMessageListenerBuffers ( bool can_be_multi_threaded )
		{
			if(!listener) return;
			
			if(can_be_multi_threaded)
			{

				{
					typedef Core::TransformChangedMessage MessageType;
					typedef Utils::OnlyLastMessageBuffer<MessageType> BufferType;
					
					listener->createMessageBuffer<MessageType, BufferType>(this, &BaseOgreLightComponent::onTransformChanged);
				}

			}
			else
			{

				{
					typedef Core::TransformChangedMessage MessageType;
					typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;

					listener->createMessageBuffer<MessageType, BufferType>(this, &BaseOgreLightComponent::onTransformChanged);
				}

				
			}
		}
		
	}
}
