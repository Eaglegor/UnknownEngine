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

		PxRigidBodyComponentsFactory::PxRigidBodyComponentsFactory(PhysXSubsystem* physx_subsystem, Core::EngineContext* engine_context):
		physx_subsystem(physx_subsystem),
		engine_context(engine_context)
		{
			CreatableObjectDesc creatable_component;
			creatable_component.type = PX_RIGID_BODY_COMPONENT_TYPE;
			creatable_component.creator = std::bind(&PxRigidBodyComponentsFactory::createPxRigidBodyComponent, this, std::placeholders::_1);
			registerCreator(creatable_component);
		}

		Core::IComponent* PxRigidBodyComponentsFactory::createPxRigidBodyComponent(const Core::ComponentDesc& desc)
		{
			PxRigidBodyComponent* result;
			result = new PxRigidBodyComponent(desc.name, desc.descriptor.apply_visitor(px_rigid_body_descriptor_getter), physx_subsystem, engine_context);
			result->initMessageListener(desc.received_messages);
			return result;
		}
		
	}
}