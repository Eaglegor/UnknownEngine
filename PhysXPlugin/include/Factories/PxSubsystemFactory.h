#pragma once

#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace Physics
	{
		class PhysXSubsystem;
		class PxComponentsFactory;
		class PxDataProvidersFactory;
		
		class PxSubsystemFactory : public Core::BaseComponentFactory
		{
		public:
			PxSubsystemFactory(PxComponentsFactory* components_factory, PxDataProvidersFactory* data_providers_factory);
			
			virtual const char* getName() const {return "Physx.SubsystemFactory";}
			
		private:
			Core::IComponent* createPxSubsystem(const Core::ComponentDesc &desc);
			void destroyPxSubsystem(Core::IComponent* component);
			
			PhysXSubsystem* physx_subsystem;
			PxComponentsFactory* components_factory;
			PxDataProvidersFactory* data_providers_factory;
		};
	}
}