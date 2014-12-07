#pragma once
#include <ResourceManager/DataProviders/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PxBoxShapeDataProvider;
		class PhysXSubsystem;
		
		class PxShapeDataProvidersFactory : public Core::BaseDataProviderFactory
		{
		public:
			PxShapeDataProvidersFactory(PhysXSubsystem *physx_subsystem);
			
		private:
			Core::IDataProvider* createPxBoxShapeDataProvider(const Core::DataProviderDesc& desc);
			
			virtual const char* getName() const override;
			
			PhysXSubsystem* physx_subsystem;
			
		};
	}
}