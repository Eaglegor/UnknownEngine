#include <Factories/OgreLightComponentsFactory.h>
#include <ComponentDesc.h>

#include <Components/Lights/OgrePointLightComponent.h>
#include <Components/Lights/OgreDirectionalLightComponent.h>
#include <Components/Lights/OgreSpotLightComponent.h>

#include <Parsers/Descriptors/OgrePointLightDescriptorParser.h>
#include <Parsers/Descriptors/OgreDirectionalLightDescriptorParser.h>
#include <Parsers/Descriptors/OgreSpotLightDescriptorParser.h>


namespace UnknownEngine {
	namespace Graphics {
		
		Core::Component* OgreLightComponentsFactory::internalCreateObject ( const Core::ComponentDesc& desc )
		{
			Core::Component* component = nullptr;
			
			if(desc.type == OGRE_POINT_LIGHT_COMPONENT_TYPE)
			{
				component = createPointLightComponent(desc);
			}
			else if(desc.type == OGRE_DIRECTIONAL_LIGHT_COMPONENT_TYPE)
			{
				component = createDirectionalLightComponent(desc);
			}
			else if(desc.type == OGRE_SPOT_LIGHT_COMPONENT_TYPE)
			{
				component = createSpotLightComponent(desc);
			}
			
			return component;
		}

		void OgreLightComponentsFactory::internalDestroyObject ( Core::Component* object )
		{
			if(object->getType() == OGRE_POINT_LIGHT_COMPONENT_TYPE)
			{
				destroyPointLightComponent(object);
			}
			else if(object->getType() == OGRE_DIRECTIONAL_LIGHT_COMPONENT_TYPE)
			{
				destroyDirectionalLightComponent(object);
			}
			else if(object->getType() == OGRE_SPOT_LIGHT_COMPONENT_TYPE)
			{
				destroySpotLightComponent(object);
			}
		}

		const std::string OgreLightComponentsFactory::getName()
		{
			return "Graphics.OgreRenderSubsystem.LightComponentsFactory";
		}

		const std::unordered_set< Core::ComponentType >& OgreLightComponentsFactory::getSupportedTypes()
		{
			return supported_types;
		}

		const bool OgreLightComponentsFactory::supportsType ( const Core::ComponentType& object_type )
		{
			return supported_types.find(object_type) != supported_types.end();
		}
		
		OgrePointLightComponent* OgreLightComponentsFactory::createPointLightComponent ( const UnknownEngine::Core::ComponentDesc& desc )
		{
			OgrePointLightComponent* component;
			
			if(!desc.descriptor.isEmpty())
			{
				component = new OgrePointLightComponent(desc.name, desc.descriptor.get<OgrePointLightComponentDescriptor>(), render_subsystem, engine_context);
			}
			else
			{
				component = new OgrePointLightComponent(desc.name, OgrePointLightDescriptorParser::parse(desc.creation_options), render_subsystem, engine_context);
			}
			
			for(const Core::ReceivedMessageDesc& message : desc.received_messages)
			{
				component->addReceivedMessageType(message);
			}
			
			return component;
		}

		void OgreLightComponentsFactory::destroyPointLightComponent ( Core::Component* object )
		{
			delete object;
		}
		
		OgreLightComponentsFactory::OgreLightComponentsFactory ( UnknownEngine::Graphics::OgreRenderSubsystem* render_subsystem, UnknownEngine::Core::EngineContext* engine_context, UnknownEngine::Core::LogHelper* log_helper ):
		BaseOgreComponentFactory(render_subsystem, engine_context, log_helper)
		{
			supported_types.insert(OGRE_POINT_LIGHT_COMPONENT_TYPE);
			supported_types.insert(OGRE_DIRECTIONAL_LIGHT_COMPONENT_TYPE);
			supported_types.insert(OGRE_SPOT_LIGHT_COMPONENT_TYPE);
		}

		OgreDirectionalLightComponent* OgreLightComponentsFactory::createDirectionalLightComponent ( const Core::ComponentDesc& desc )
		{
			OgreDirectionalLightComponent* component;
			
			if(!desc.descriptor.isEmpty())
			{
				component = new OgreDirectionalLightComponent(desc.name, desc.descriptor.get<OgreDirectionalLightComponentDescriptor>(), render_subsystem, engine_context);
			}
			else
			{
				component = new OgreDirectionalLightComponent(desc.name, OgreDirectionalLightDescriptorParser::parse(desc.creation_options), render_subsystem, engine_context);
			}
			
			for(const Core::ReceivedMessageDesc& message : desc.received_messages)
			{
				component->addReceivedMessageType(message);
			}
			
			return component;
		}

		void OgreLightComponentsFactory::destroyDirectionalLightComponent ( Core::Component* object )
		{
			delete object;
		}

		OgreSpotLightComponent* OgreLightComponentsFactory::createSpotLightComponent ( const Core::ComponentDesc& desc )
		{
			OgreSpotLightComponent* component;
			
			if(!desc.descriptor.isEmpty())
			{
				component = new OgreSpotLightComponent(desc.name, desc.descriptor.get<OgreSpotLightComponentDescriptor>(), render_subsystem, engine_context);
			}
			else
			{
				component = new OgreSpotLightComponent(desc.name, OgreSpotLightDescriptorParser::parse(desc.creation_options), render_subsystem, engine_context);
			}
			
			for(const Core::ReceivedMessageDesc& message : desc.received_messages)
			{
				component->addReceivedMessageType(message);
			}
			
			return component;
		}

		void OgreLightComponentsFactory::destroySpotLightComponent ( Core::Component* object )
		{
			delete object;
		}

		
	}
}
