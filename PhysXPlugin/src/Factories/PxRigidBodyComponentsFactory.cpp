#include <Factories/PxRigidBodyComponentsFactory.h>
#include <Components/PxRigidBodyComponent.h>
#include <Parsers/PxRigidBodyComponentDescriptorGetter.h>

namespace UnknownEngine
{
	namespace Physics
	{
		
		static PxRigidBodyComponentDescriptorGetter px_rigid_body_descriptor_getter;
		
		const char* PxRigidBodyComponentsFactory::getName()
		{
			return "Physics.PhysXPlugin.PxRigidBodyComponentsFactory";
		}

		PxRigidBodyComponentsFactory::PxRigidBodyComponentsFactory(PhysXSubsystem* physx_subsystem)
		{
			CreatableObjectDesc creatable_data_provider;
			creatable_data_provider.type = PX_RIGID_BODY_COMPONENT_TYPE;
			creatable_data_provider.creator = std::bind(&PxRigidBodyComponentsFactory::createPxRigidBodyComponent, this, std::placeholders::_1);
			registerCreator(creatable_data_provider);
		}

		Core::IComponent* PxRigidBodyComponentsFactory::createPxRigidBodyComponent(const Core::ComponentDesc& desc)
		{
			PxRigidBodyComponent* result;
			result = new PxRigidBodyComponent(desc.name, desc.descriptor.apply_visitor(px_rigid_body_descriptor_getter), physx_subsystem);
			return result;
		}
		
	}
}