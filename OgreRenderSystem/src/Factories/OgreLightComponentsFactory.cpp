#include <Factories/OgreLightComponentsFactory.h>
#include <ComponentDesc.h>
#include <Components/OgrePointLightComponent.h>
#include <Parsers/OgrePointLightDescriptorParser.h>

namespace UnknownEngine {
	namespace Graphics {
		
		Core::Component* OgreLightComponentsFactory::createObject ( const Core::ComponentDesc& desc )
		{
			Core::Component* component = nullptr;
			
			if(desc.type == OGRE_POINT_LIGHT_COMPONENT_TYPE)
			{
				component = createPointLightComponent(desc);
			}
			
			return component;
		}

		void OgreLightComponentsFactory::destroyObject ( Core::Component* object )
		{
			if(object->getType() == OGRE_POINT_LIGHT_COMPONENT_TYPE)
			{
				destroyPointLightComponent(object);
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
				component = new OgrePointLightComponent(desc.name, desc.descriptor.get<OgrePointLightComponent::Descriptor>(), render_subsystem, engine_context);
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
		engine_context(engine_context),
		render_subsystem(render_subsystem),
		log_helper(log_helper)
		{
			supported_types.insert(OGRE_POINT_LIGHT_COMPONENT_TYPE);
		}

		
	}
}
