#pragma once

#include <EngineContext.h>
#include <ComponentDesc.h>
#include <MessageSystem/BaseMessageListener.h>
#include <Listeners/BaseMessageListenersFactory.h>
#include <OgreRenderSubsystem_fwd.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		template<typename ComponentClass, typename ComponentDescriptorClass, typename ComponentDescriptorParserClass>
		Core::IComponent* defaultCreator( const Core::ComponentDesc& desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context )
		{
			ComponentClass* component;
			if ( !desc.descriptor.isEmpty() )
			{
				component = new ComponentClass ( desc.name, desc.descriptor.get<ComponentDescriptorClass>(), render_subsystem, engine_context );
			}
			else
			{
				component = new ComponentClass ( desc.name, ComponentDescriptorParserClass::parse ( desc.creation_options ), render_subsystem, engine_context );
			}
			
			std::unique_ptr<Core::BaseMessageListener> listener = Utils::BaseMessageListenersFactory::createBaseMessageListener(
				std::string(component->getName())+".Listener",
				engine_context,
				desc.received_messages
			);
			
			component->setMessageListener(std::move(listener));	
			
			return component;
		}
		
		template<typename ComponentClass, typename ComponentDescriptorClass, typename ComponentDescriptorParserClass>
		std::function< Core::IComponent* (const Core::ComponentDesc& desc) > getDefaultCreator( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context )
		{
			return std::bind( 
				&defaultCreator<ComponentClass, ComponentDescriptorClass, ComponentDescriptorParserClass>,
				std::placeholders::_1,
				render_subsystem,
				engine_context
			);
		}
		
	}
}