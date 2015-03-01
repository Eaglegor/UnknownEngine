#include <Factories/PxSubsystemFactory.h>
#include <Factories/PxComponentsFactory.h>
#include <Factories/PxDataProvidersFactory.h>
#include <PhysXSubsystem.h>
#include <Parsers/PhysXSubsystemDescriptorGetter.h>
#include <ComponentSystem/ComponentDesc.h>

namespace UnknownEngine
{
	namespace Physics
	{
		static PhysXSubsystemDescriptorGetter subsystem_descriptor_getter;
		
		PxSubsystemFactory::PxSubsystemFactory ( PxComponentsFactory* components_factory, PxDataProvidersFactory* data_providers_factory ):
		physx_subsystem(nullptr),
		components_factory(components_factory),
		data_providers_factory(data_providers_factory)
		{
			CreatableObjectDesc creatable_object;
			creatable_object.type = PhysXSubsystem::getTypeName();
			creatable_object.creator = std::bind(&PxSubsystemFactory::createPxSubsystem, this, std::placeholders::_1);
			creatable_object.deleter = std::bind(&PxSubsystemFactory::destroyPxSubsystem, this, std::placeholders::_1);
			registerCreator(creatable_object);
		}

		Core::IComponent* PxSubsystemFactory::createPxSubsystem ( const Core::ComponentDesc& desc )
		{
			if(physx_subsystem) return nullptr;
			
			PhysXSubsystemDesc descriptor = desc.descriptor.apply_visitor(subsystem_descriptor_getter);
			physx_subsystem = new PhysXSubsystem(desc.name.c_str(), descriptor);
			
			components_factory->setPhysXSubsystem(physx_subsystem);
			data_providers_factory->setPhysXSubsystem(physx_subsystem);
			return physx_subsystem;
		}

		void PxSubsystemFactory::destroyPxSubsystem ( Core::IComponent* component )
		{
			delete physx_subsystem;
			physx_subsystem = nullptr;
			components_factory->setPhysXSubsystem(nullptr);
			data_providers_factory->setPhysXSubsystem(nullptr);
		}
		
	}
}