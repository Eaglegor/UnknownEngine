#include <Components/OgrePointLightComponent.h>
#include <Converters/OgreVector3Converter.h>
#include <OgreLight.h>
#include <OgreSceneNode.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgrePointLightComponent::OgrePointLightComponent ( const std::string& name, const Descriptor& desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ) : 
		BaseOgreLightComponent ( name, render_subsystem, engine_context, desc.light_settings ), 
		desc(desc)
		{}
		
		UnknownEngine::Core::ComponentType OgrePointLightComponent::getType()
		{
			return OGRE_POINT_LIGHT_COMPONENT_TYPE;
		}

		void OgrePointLightComponent::init ( const UnknownEngine::Core::Entity* parent_entity )
		{
			BaseOgreLightComponent::init(parent_entity);
			ogre_light->setType(Ogre::Light::LT_POINT);
			
			ogre_scene_node->setPosition( OgreVector3Converter::toOgreVector(desc.initial_transform.getPosition()) );
		}
	}
}
