#include <stdafx.h>

#include <Components/Lights/BaseOgreLightComponent.h>
#include <OgreRenderSubsystem.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreColourValueConverter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>


namespace UnknownEngine
{
	namespace Graphics
	{

		BaseOgreLightComponent::BaseOgreLightComponent ( const std::string& name, UnknownEngine::Graphics::OgreRenderSubsystem* render_subsystem, const UnknownEngine::Graphics::OgreLightSettings& light_settings, Core::IComponent* transform_provider  ):
		BaseOgreComponent(name, render_subsystem),
		light_settings(light_settings),
		transform_provider(transform_provider)
		{
		}
		
		BaseOgreLightComponent::~BaseOgreLightComponent()
		{
		}
		
		void BaseOgreLightComponent::internalInit(  )
		{
			ogre_light = getRenderSubsystem()->getSceneManager()->createLight(Ogre::String(getName()) + ".Light");
			ogre_scene_node = getRenderSubsystem()->getSceneManager()->getRootSceneNode()->createChildSceneNode(Ogre::String(getName())+".SceneNode");
			
			Ogre::ColourValue diffuse_color = light_settings.diffuse_color.get() * light_settings.intensity.get();
			ogre_light->setDiffuseColour( diffuse_color );
			
			Ogre::ColourValue specular_color = light_settings.specular_color.get() * light_settings.intensity.get();
			ogre_light->setSpecularColour( specular_color );
			
			if(light_settings.attenuation.isExplicitlyInitialized())
			{
				const OgreLightSettings::Attenuation& att = light_settings.attenuation.get();
				ogre_light->setAttenuation(att.range, att.constant, att.linear, att.quadratic);
			}
			
			if(light_settings.cast_shadows.isExplicitlyInitialized())
			{
				ogre_light->setCastShadows(light_settings.cast_shadows.get());
			}
			
			ogre_scene_node->attachObject(ogre_light);
			
			if(transform_provider)
			{
				transform_provider->addListener(&transform_adapter);
			}
			
		}
		
		void BaseOgreLightComponent::internalShutdown()
		{
			if(transform_provider)
			{
				transform_provider->removeListener(&transform_adapter);
			}
			
			ogre_scene_node->detachObject(ogre_light);
			
			getRenderSubsystem()->getSceneManager()->destroyLight(ogre_light);
			getRenderSubsystem()->getSceneManager()->destroySceneNode(ogre_scene_node);
		}

		void BaseOgreLightComponent::setOrientation ( const Math::Quaternion& quaternion )
		{
			this->ogre_scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(quaternion) );
		}

		void BaseOgreLightComponent::setPosition ( const Math::Vector3& position )
		{
			this->ogre_scene_node->setPosition( OgreVector3Converter::toOgreVector(position) );
		}

		void BaseOgreLightComponent::setTransform ( const Math::Transform& transform )
		{
			this->ogre_scene_node->setPosition( OgreVector3Converter::toOgreVector(transform.getPosition()) );
			this->ogre_scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(transform.getOrientation()) );
		}
		
		void BaseOgreLightComponent::_update()
		{
			transform_adapter.apply(this);
		}
		
	}
}
