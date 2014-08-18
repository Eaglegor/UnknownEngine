#include <Components/Lights/OgrePointLightComponent.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgrePointLightComponent::OgrePointLightComponent ( const std::string& name, const Descriptor& desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ) : 
		BaseOgreLightComponent ( name, render_subsystem, engine_context, desc.light_settings ), 
		desc(desc)
		{
			if(desc.log_level > Core::LogMessage::Severity::LOG_SEVERITY_NONE)
			{
				log_helper.reset(new Core::LogHelper ( getName(), desc.log_level, engine_context ));
			}
			
			LOG_INFO ( log_helper, "Logger initialized" );			
		}
		
		OgrePointLightComponent::~OgrePointLightComponent()
		{
		}
		
		UnknownEngine::Core::ComponentType OgrePointLightComponent::getType()
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
