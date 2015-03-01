#include <stdafx.h>
#include <Factories/PxComponentsFactory.h>
#include <Components/PxRigidBodyComponent.h>
#include <Components/PxFixedJointComponent.h>
#include <Parsers/PxRigidBodyComponentDescriptorGetter.h>
#include <Parsers/PxFixedJointComponentDescriptorGetter.h>
#include <ComponentSystem/ComponentDesc.h>

namespace UnknownEngine
{
	namespace Physics
	{
		
		static PxRigidBodyComponentDescriptorGetter px_rigid_body_descriptor_getter;
		static PxFixedJointComponentDescriptorGetter px_fixed_joint_descriptor_getter;

		PxComponentsFactory::PxComponentsFactory():
		physx_subsystem(nullptr)
		{
			CreatableObjectDesc creatable_component;
			creatable_component.type = PxRigidBodyComponent::getTypeName();
			creatable_component.creator = std::bind(&PxComponentsFactory::createPxRigidBodyComponent, this, std::placeholders::_1);
			registerCreator(creatable_component);
			
			creatable_component.type = PxFixedJointComponent::getTypeName();
			creatable_component.creator = std::bind(&PxComponentsFactory::createPxFixedJointComponent, this, std::placeholders::_1);
			registerCreator(creatable_component);
		}

		void PxComponentsFactory::setPhysXSubsystem ( PhysXSubsystem* physx_subsystem )
		{
			this->physx_subsystem = physx_subsystem;
		}
		
		Core::IComponent* PxComponentsFactory::createPxRigidBodyComponent(const Core::ComponentDesc& desc)
		{
			if(!physx_subsystem) return nullptr;
			PxRigidBodyComponent* result;
			result = new PxRigidBodyComponent(desc.name, desc.descriptor.apply_visitor(px_rigid_body_descriptor_getter), physx_subsystem);
			return result;
		}
		
		Core::IComponent* PxComponentsFactory::createPxFixedJointComponent(const Core::ComponentDesc& desc)
		{
			if(!physx_subsystem) return nullptr;
			PxFixedJointComponent* result;
			result = new PxFixedJointComponent(desc.name, desc.descriptor.apply_visitor(px_fixed_joint_descriptor_getter), physx_subsystem);
			return result;
		}
	}
}