#include <stdafx.h>
#include <Factories/SimpleBehaviorsFactory.h>
#include <ComponentSystem/ComponentDesc.h>
#include <Components/SimpleRotationComponent.h>
#include <EngineContext.h>
#include <SimpleBehaviorsPerformer.h>
#include <Components/MouseLookComponent.h>
#include <Parsers/MouseLookComponentDescriptorGetter.h>
#include <Components/SimpleCreateJointComponent.h>
#include <Parsers/SimpleCreateJointComponentDescriptorGetter.h>
#include <Parsers/SimpleRotationComponentDescriptorGetter.h>
#include <Parsers/SimpleEngineStopperComponentDescriptorGetter.h>
#include <Components/SimpleEngineStopperComponent.h>

#include <Transform/Transform.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		
		static SimpleRotationComponentDescriptorGetter rotation_descriptor_getter;
		static MouseLookComponentDescriptorGetter mouse_look_descriptor_getter;
		static SimpleCreateJointComponentDescriptorGetter simple_create_joint_descriptor_getter;
        static SimpleEngineStopperComponentDescriptorGetter simple_engine_stopper_descriptor_getter;
		
		SimpleBehaviorsFactory::SimpleBehaviorsFactory ( UnknownEngine::Core::EngineContext* engine_context):
		engine_context(engine_context)
		{
			CreatableObjectDesc creatable_component;
			creatable_component.type = SIMPLE_ROTATION_COMPONENT_TYPE;
			creatable_component.creator = std::bind(&SimpleBehaviorsFactory::createSimpleRotationComponent, this, std::placeholders::_1);
			creatable_component.deleter = std::bind(&SimpleBehaviorsFactory::destroySimpleBehaviorComponent, this, std::placeholders::_1);
			registerCreator(creatable_component);
			
			creatable_component.type = MOUSE_LOOK_COMPONENT_TYPE;
			creatable_component.creator = std::bind(&SimpleBehaviorsFactory::createMouseLookComponent, this, std::placeholders::_1);
			creatable_component.deleter = std::bind(&SimpleBehaviorsFactory::destroySimpleBehaviorComponent, this, std::placeholders::_1);
			registerCreator(creatable_component);
			
			creatable_component.type = SIMPLE_CREATE_JOINT_COMPONENT_TYPE;
            creatable_component.creator = std::bind(&SimpleBehaviorsFactory::createSimpleCreateJointComponent, this, std::placeholders::_1);
            creatable_component.deleter = std::bind(&SimpleBehaviorsFactory::destroySimpleBehaviorComponent, this, std::placeholders::_1);
            registerCreator(creatable_component);

            creatable_component.type = SimpleEngineStopperComponent::getTypeName();
            creatable_component.creator = std::bind(&SimpleBehaviorsFactory::createSimpleEngineStopperComponent, this, std::placeholders::_1);
            creatable_component.deleter = std::bind(&SimpleBehaviorsFactory::destroySimpleBehaviorComponent, this, std::placeholders::_1);
            registerCreator(creatable_component);
		}

		Core::IComponent* SimpleBehaviorsFactory::createSimpleRotationComponent ( const Core::ComponentDesc& desc )
		{
			SimpleRotationComponentDesc component_desc = desc.descriptor.apply_visitor(rotation_descriptor_getter);
			SimpleRotationComponent* component = new SimpleRotationComponent(desc.name, component_desc, engine_context);
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
			SimpleCreateJointComponent* component = new SimpleCreateJointComponent(desc.name, component_desc, engine_context);
			return component;
		}

        Core::IComponent* SimpleBehaviorsFactory::createSimpleEngineStopperComponent ( const Core::ComponentDesc& desc )
        {
            SimpleEngineStopperDesc component_desc = desc.descriptor.apply_visitor(simple_engine_stopper_descriptor_getter);
            SimpleEngineStopperComponent* component = new SimpleEngineStopperComponent(desc.name.c_str(), component_desc);
            return component;
        }

		void SimpleBehaviorsFactory::destroySimpleBehaviorComponent ( Core::IComponent* object )
		{
			//behaviors_performer->removeSimpleBehaviorComponent( static_cast<SimpleBehaviorComponent*>(object) );
			delete object;
		}
		
		const char* SimpleBehaviorsFactory::getName() const
		{
			return "SimpleBehaviorPlugin.Factories.SimpleBehaviorFactory";
		}

	}
}