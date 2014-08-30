#include <stdafx.h>

#include <Factories/OgreLightComponentsFactory.h>

#include <Components/Lights/OgrePointLightComponent.h>
#include <Parsers/Descriptors/OgrePointLightDescriptorParser.h>

#include <Components/Lights/OgreDirectionalLightComponent.h>
#include <Parsers/Descriptors/OgreDirectionalLightDescriptorParser.h>

#include <Components/Lights/OgreSpotLightComponent.h>
#include <Parsers/Descriptors/OgreSpotLightDescriptorParser.h>

#include <Listeners/BaseMessageListenersFactory.h>

#include <Factories/DefaultComponentCreatorFunc.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreLightComponentsFactory::OgreLightComponentsFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper ) :
		BaseOgreComponentFactory ( render_subsystem, engine_context, log_helper )
		{
			CreatableObjectDesc creatable_component;
			
			creatable_component.type = OGRE_POINT_LIGHT_COMPONENT_TYPE;
			creatable_component.creator = getDefaultCreator<OgrePointLightComponent, OgrePointLightComponentDescriptor, OgrePointLightDescriptorParser>(render_subsystem, engine_context);
			registerCreator(creatable_component);
			
			creatable_component.type = OGRE_DIRECTIONAL_LIGHT_COMPONENT_TYPE;
			creatable_component.creator = getDefaultCreator<OgreDirectionalLightComponent, OgreDirectionalLightComponentDescriptor, OgreDirectionalLightDescriptorParser>(render_subsystem, engine_context);
			registerCreator(creatable_component);
			
			creatable_component.type = OGRE_SPOT_LIGHT_COMPONENT_TYPE;
			creatable_component.creator = getDefaultCreator<OgreSpotLightComponent, OgreSpotLightComponentDescriptor, OgreSpotLightDescriptorParser>(render_subsystem, engine_context);
			registerCreator(creatable_component);
		}

		const char* OgreLightComponentsFactory::getName()
		{
			return "Graphics.OgreRenderSubsystem.LightComponentsFactory";
		}

	}
}
