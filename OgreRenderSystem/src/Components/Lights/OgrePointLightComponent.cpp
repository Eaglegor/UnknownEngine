#include <stdafx.h>

#include <Components/Lights/OgrePointLightComponent.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgrePointLightComponent::OgrePointLightComponent ( const std::string& name, const OgrePointLightComponentDescriptor& desc, OgreRenderSubsystem* render_subsystem) : 
		BaseOgreLightComponent ( name, render_subsystem, desc.light_settings ), 
		desc(desc),
		logger(name.c_str(), desc.log_level)
		{
			LOG_INFO ( logger, "Logger initialized" );			
		}
		
		OgrePointLightComponent::~OgrePointLightComponent()
		{
		}

		void OgrePointLightComponent::internalInit ()
		{
			BaseOgreLightComponent::internalInit();
			ogre_light->setType(Ogre::Light::LT_POINT);
			
			ogre_scene_node->setPosition( OgreVector3Converter::toOgreVector(desc.initial_transform.getPosition()) );
			ogre_scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(desc.initial_transform.getOrientation()) );
		}
	}
}
