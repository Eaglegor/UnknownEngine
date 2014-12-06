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
		
		OgrePointLightComponent::OgrePointLightComponent ( const std::string& name, const OgrePointLightComponentDescriptor& desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ) : 
		BaseOgreLightComponent ( name, render_subsystem, engine_context, desc.light_settings ), 
		desc(desc)
		{
			logger = CREATE_LOGGER(getName(), desc.log_level);

			LOG_INFO ( logger, "Logger initialized" );			
		}
		
		OgrePointLightComponent::~OgrePointLightComponent()
		{
			RELEASE_LOGGER(logger);
		}
		
		UnknownEngine::Core::ComponentType OgrePointLightComponent::getType() const
		{
			return OGRE_POINT_LIGHT_COMPONENT_TYPE;
		}

		void OgrePointLightComponent::internalInit (const UnknownEngine::Core::Entity* parent_entity)
		{
			BaseOgreLightComponent::internalInit(parent_entity);
			ogre_light->setType(Ogre::Light::LT_POINT);
			
			ogre_scene_node->setPosition( OgreVector3Converter::toOgreVector(desc.initial_transform.getPosition()) );
			ogre_scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(desc.initial_transform.getOrientation()) );
		}
	}
}
