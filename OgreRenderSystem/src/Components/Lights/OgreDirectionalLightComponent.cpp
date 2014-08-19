#include <Components/Lights/OgreDirectionalLightComponent.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreDirectionalLightComponent::OgreDirectionalLightComponent ( const std::string& name, const OgreDirectionalLightComponentDescriptor& desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ) : 
		BaseOgreLightComponent ( name, render_subsystem, engine_context, desc.light_settings ), 
		desc(desc)
		{
			if(desc.log_level > Core::LogMessage::Severity::LOG_SEVERITY_NONE)
			{
				log_helper.reset( new Core::LogHelper ( getName(), desc.log_level, engine_context ) );
			}
			
			LOG_INFO ( log_helper, "Logger initialized" );			
		}
		
		OgreDirectionalLightComponent::~OgreDirectionalLightComponent()
		{
		}
		
		UnknownEngine::Core::ComponentType OgreDirectionalLightComponent::getType()
		{
			return OGRE_DIRECTIONAL_LIGHT_COMPONENT_TYPE;
		}

		void OgreDirectionalLightComponent::internalInit (const UnknownEngine::Core::Entity* parent_entity)
		{
			BaseOgreLightComponent::internalInit(parent_entity);
			ogre_light->setType(Ogre::Light::LT_DIRECTIONAL);
			
			ogre_light->setPosition( OgreVector3Converter::toOgreVector(desc.initial_transform.getPosition()) );
			
			if(desc.initial_look_at.is_initialized())
			{
				Ogre::Vector3 position = ogre_light->getPosition();
				Ogre::Vector3 look_at_point = OgreVector3Converter::toOgreVector(desc.initial_look_at.get());
				ogre_light->setDirection( look_at_point - position );
			}
			else if(desc.initial_direction.is_initialized())
			{
				ogre_light->setDirection( OgreVector3Converter::toOgreVector(desc.initial_direction.get()) );
			}
			else
			{
				ogre_scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(desc.initial_transform.getOrientation()) );
			}
		}
	}
}
