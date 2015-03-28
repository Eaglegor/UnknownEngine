#include <stdafx.h>

#include <Components/Lights/OgreDirectionalLightComponent.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreDirectionalLightComponent::OgreDirectionalLightComponent ( const std::string& name, const OgreDirectionalLightComponentDescriptor& desc, OgreRenderSubsystem* render_subsystem) : 
		BaseOgreLightComponent ( name, render_subsystem, desc.light_settings, desc.transform_provider ), 
		desc(desc),
		logger(name.c_str(), desc.log_level)
		{
			LOG_INFO ( logger, "Logger initialized" );			
		}
		
		OgreDirectionalLightComponent::~OgreDirectionalLightComponent()
		{
		}

		void OgreDirectionalLightComponent::internalInit ()
		{
			BaseOgreLightComponent::internalInit();
			ogre_light->setType(Ogre::Light::LT_DIRECTIONAL);
			
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
				ogre_scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(desc.initial_transform->orientation) );
			}
		}
	}
}
