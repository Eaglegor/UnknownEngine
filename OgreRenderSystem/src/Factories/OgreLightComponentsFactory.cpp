#include <stdafx.h>

#include <Factories/OgreLightComponentsFactory.h>

#include <Components/Lights/OgrePointLightComponent.h>
#include <Parsers/Descriptors/OgrePointLightDescriptorParser.h>

#include <Components/Lights/OgreDirectionalLightComponent.h>
#include <Parsers/Descriptors/OgreDirectionalLightDescriptorParser.h>

#include <Components/Lights/OgreSpotLightComponent.h>
#include <Parsers/Descriptors/OgreSpotLightDescriptorParser.h>

#include <Factories/DefaultComponentCreatorFunc.h>

#include <Factories/OgreGetDescriptorVisitor.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		static OgreGetDescriptorVisitor<OgrePointLightComponentDescriptor, OgrePointLightDescriptorParser> point_light_descriptor_getter;
		static OgreGetDescriptorVisitor<OgreDirectionalLightComponentDescriptor, OgreDirectionalLightDescriptorParser> directional_light_descriptor_getter;
		static OgreGetDescriptorVisitor<OgreSpotLightComponentDescriptor, OgreSpotLightDescriptorParser> spot_light_descriptor_getter;
		
		OgreLightComponentsFactory::OgreLightComponentsFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Utils::LogHelper* log_helper ) :
		BaseOgreComponentFactory ( render_subsystem, engine_context, log_helper )
		{
			CreatableObjectDesc creatable_component;
			
			creatable_component.type = OGRE_POINT_LIGHT_COMPONENT_TYPE;
			creatable_component.creator = getDefaultCreator<OgrePointLightComponent>(point_light_descriptor_getter, render_subsystem, engine_context);
			registerCreator(creatable_component);
			
			creatable_component.type = OGRE_DIRECTIONAL_LIGHT_COMPONENT_TYPE;
			creatable_component.creator = getDefaultCreator<OgreDirectionalLightComponent>(directional_light_descriptor_getter, render_subsystem, engine_context);
			registerCreator(creatable_component);
			
			creatable_component.type = OGRE_SPOT_LIGHT_COMPONENT_TYPE;
			creatable_component.creator = getDefaultCreator<OgreSpotLightComponent>(spot_light_descriptor_getter, render_subsystem, engine_context);
			registerCreator(creatable_component);
		}

		const char* OgreLightComponentsFactory::getName()
		{
			return "Graphics.OgreRenderSubsystem.LightComponentsFactory";
		}

	}
}
