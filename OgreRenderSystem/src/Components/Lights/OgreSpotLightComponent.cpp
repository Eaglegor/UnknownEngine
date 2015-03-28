#include <stdafx.h>

#include <Components/Lights/OgreSpotLightComponent.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreSpotLightComponent::OgreSpotLightComponent ( const std::string& name, const OgreSpotLightComponentDescriptor& desc, OgreRenderSubsystem* render_subsystem) : 
		BaseOgreLightComponent ( name, render_subsystem, desc.light_settings, desc.transform_provider ), 
		desc(desc),
		logger(name.c_str(), desc.log_level)
		{
			LOG_INFO ( logger, "Logger initialized" );			
		}
		
		OgreSpotLightComponent::~OgreSpotLightComponent()
		{
		}

		void OgreSpotLightComponent::internalInit ()
		{
			BaseOgreLightComponent::internalInit();
			ogre_light->setType(Ogre::Light::LT_SPOTLIGHT);
			
			//ogre_light->setPosition( OgreVector3Converter::toOgreVector(desc.initial_transform.getPosition()) );
			transform_adapter.setTransform(desc.initial_transform.get());
			
			if(desc.initial_look_at.isExplicitlyInitialized())
			{
				Ogre::Vector3 position = ogre_light->getPosition();
				Ogre::Vector3 look_at_point = OgreVector3Converter::toOgreVector(desc.initial_look_at.get());
				ogre_light->setDirection( look_at_point - position );
			}
			else if(desc.initial_direction.isExplicitlyInitialized())
			{
				ogre_light->setDirection( OgreVector3Converter::toOgreVector(desc.initial_direction.get()) );
			}
			else
			{
				ogre_scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(desc.initial_transform->orientation));
			}
			
			if(desc.inner_angle.isExplicitlyInitialized()) ogre_light->setSpotlightInnerAngle( Ogre::Degree(desc.inner_angle.get()) );
			if(desc.outer_angle.isExplicitlyInitialized()) ogre_light->setSpotlightOuterAngle( Ogre::Degree(desc.outer_angle.get()) );
			if(desc.falloff.isExplicitlyInitialized()) ogre_light->setSpotlightFalloff(desc.falloff.get());
			
		}
	}
}
