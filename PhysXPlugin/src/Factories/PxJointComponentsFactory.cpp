#include <stdafx.h>
#include <Factories/PxJointComponentsFactory.h>
#include <Components/PxFixedJointComponent.h>
#include <Parsers/PxFixedJointComponentDescriptorGetter.h>

namespace UnknownEngine
{
	namespace Physics
	{
		
		static PxFixedJointComponentDescriptorGetter px_fixed_joint_descriptor_getter;
		
		const char* PxJointComponentsFactory::getName()
		{
			return "Physics.PhysXPlugin.PxJointComponentsFactory";
		}

		PxJointComponentsFactory::PxJointComponentsFactory(PhysXSubsystem* physx_subsystem, Core::EngineContext* engine_context) :
		physx_subsystem(physx_subsystem),
		engine_context(engine_context)
		{
			CreatableObjectDesc creatable_component;
			creatable_component.type = PX_FIXED_JOINT_COMPONENT_TYPE;
			creatable_component.creator = std::bind(&PxJointComponentsFactory::createPxFixedJointComponent, this, std::placeholders::_1);
			registerCreator(creatable_component);
		}

		Core::IComponent* PxJointComponentsFactory::createPxFixedJointComponent(const Core::ComponentDesc& desc)
		{
			PxFixedJointComponent* result;
			result = new PxFixedJointComponent(desc.name, desc.descriptor.apply_visitor(px_fixed_joint_descriptor_getter), physx_subsystem, engine_context);
			return result;
		}
		
	}
}