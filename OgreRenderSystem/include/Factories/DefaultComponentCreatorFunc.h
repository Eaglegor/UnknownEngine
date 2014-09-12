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
		
		template<typename ComponentClass, typename GetDescriptorVisitorClass>
		Core::IComponent* defaultCreator( const Core::ComponentDesc& desc, const GetDescriptorVisitorClass& get_descriptor_visitor, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context )
		{
			ComponentClass* component = new ComponentClass (desc.name, desc.descriptor.apply_visitor(get_descriptor_visitor), render_subsystem, engine_context);
			
			std::unique_ptr<Core::BaseMessageListener> listener = Utils::BaseMessageListenersFactory::createBaseMessageListener(
				std::string(component->getName())+".Listener",
				engine_context,
				desc.received_messages
			);
			
			component->setMessageListener(std::move(listener));	
			
			return component;
		}
		
		template<typename ComponentClass, typename GetDescriptorVisitorClass>
		std::function< Core::IComponent* (const Core::ComponentDesc& desc) > getDefaultCreator(const GetDescriptorVisitorClass& get_descriptor_visitor, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context )
		{
			return std::bind( 
				&defaultCreator<ComponentClass, GetDescriptorVisitorClass>,
				std::placeholders::_1,
				get_descriptor_visitor,
				render_subsystem,
				engine_context
			);
		}
		
	}
}