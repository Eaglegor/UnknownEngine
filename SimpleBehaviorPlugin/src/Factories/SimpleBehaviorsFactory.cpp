#include <stdafx.h>
#include <Factories/SimpleBehaviorsFactory.h>
#include <ComponentSystem/ComponentDesc.h>
#include <Components/SimpleRotationComponent.h>
#include <EngineContext.h>
#include <SimpleBehaviorsPerformer.h>
#include <Components/MouseLookComponent.h>
#include <Components/TransformProxyComponent.h>
#include <Parsers/MouseLookComponentDescriptorGetter.h>
#include <Components/SimpleCreateJointComponent.h>
#include <Parsers/SimpleCreateJointComponentDescriptorGetter.h>
#include <Parsers/SimpleRotationComponentDescriptorGetter.h>
#include <Parsers/SimpleStopperComponentDescriptorGetter.h>
#include <Parsers/TransformProxyComponentDescriptorGetter.h>
#include <Components/SimpleStopperComponent.h>

#include <Transform/Transform.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		
		static SimpleRotationComponentDescriptorGetter rotation_descriptor_getter;
		static MouseLookComponentDescriptorGetter mouse_look_descriptor_getter;
		static SimpleCreateJointComponentDescriptorGetter simple_create_joint_descriptor_getter;
        static SimpleStopperComponentDescriptorGetter simple_stopper_descriptor_getter;
		static TransformProxyComponentDescriptorGetter transform_proxy_descriptor_getter;
		
		SimpleBehaviorsFactory::SimpleBehaviorsFactory ()
		{
			CreatableObjectDesc creatable_component;
			creatable_component.type = SimpleRotationComponent::getTypeName();
			creatable_component.creator = std::bind(&SimpleBehaviorsFactory::createSimpleRotationComponent, this, std::placeholders::_1);
			registerCreator(creatable_component);
			
			creatable_component.type = MouseLookComponent::getTypeName();
			creatable_component.creator = std::bind(&SimpleBehaviorsFactory::createMouseLookComponent, this, std::placeholders::_1);
			registerCreator(creatable_component);
			
			creatable_component.type = SimpleCreateJointComponent::getTypeName();
            creatable_component.creator = std::bind(&SimpleBehaviorsFactory::createSimpleCreateJointComponent, this, std::placeholders::_1);
            registerCreator(creatable_component);

            creatable_component.type = SimpleStopperComponent::getTypeName();
            creatable_component.creator = std::bind(&SimpleBehaviorsFactory::createSimpleStopperComponent, this, std::placeholders::_1);
            registerCreator(creatable_component);
			
			creatable_component.type = TransformProxyComponent::getTypeName();
            creatable_component.creator = std::bind(&SimpleBehaviorsFactory::createTransformProxyComponent, this, std::placeholders::_1);
            registerCreator(creatable_component);
		}

		Core::IComponent* SimpleBehaviorsFactory::createSimpleRotationComponent ( const Core::ComponentDesc& desc )
		{
			SimpleRotationComponentDesc component_desc = desc.descriptor.apply_visitor(rotation_descriptor_getter);
			SimpleRotationComponent* component = new SimpleRotationComponent(desc.name, component_desc);
			return component;
		}
		
		Core::IComponent* SimpleBehaviorsFactory::createMouseLookComponent ( const Core::ComponentDesc& desc )
		{
			MouseLookComponentDesc component_desc = desc.descriptor.apply_visitor(mouse_look_descriptor_getter);
			MouseLookComponent* component = new MouseLookComponent(desc.name, component_desc);
			return component;
		}
		
		Core::IComponent* SimpleBehaviorsFactory::createSimpleCreateJointComponent ( const Core::ComponentDesc& desc )
		{
			SimpleCreateJointComponentDesc component_desc = desc.descriptor.apply_visitor(simple_create_joint_descriptor_getter);
			SimpleCreateJointComponent* component = new SimpleCreateJointComponent(desc.name, component_desc);
			return component;
		}

        Core::IComponent* SimpleBehaviorsFactory::createSimpleStopperComponent ( const Core::ComponentDesc& desc )
        {
            SimpleStopperDesc component_desc = desc.descriptor.apply_visitor(simple_stopper_descriptor_getter);
            SimpleStopperComponent* component = new SimpleStopperComponent(desc.name.c_str(), component_desc);
            return component;
        }

		Core::IComponent* SimpleBehaviorsFactory::createTransformProxyComponent ( const Core::ComponentDesc& desc )
		{
			TransformProxyComponentDesc component_desc = desc.descriptor.apply_visitor(transform_proxy_descriptor_getter);
            TransformProxyComponent* component = new TransformProxyComponent(desc.name.c_str(), component_desc);
            return component;
		}
        
		const char* SimpleBehaviorsFactory::getName() const
		{
			return "SimpleBehaviorPlugin.Factories.SimpleBehaviorFactory";
		}

	}
}