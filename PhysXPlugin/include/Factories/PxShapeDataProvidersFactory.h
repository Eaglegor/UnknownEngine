#pragma once
#include <DataProvider/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PxBoxShapeDataProvider;
		class PhysXSubsystem;
		
		class PxShapeDataProvidersFactory : public Loader::BaseDataProviderFactory
		{
		public:
			PxShapeDataProvidersFactory(PhysXSubsystem *physx_subsystem);
			
		private:
			Loader::IDataProvider* createPxBoxShapeDataProvider(const Loader::DataProviderDesc& desc);
			
			virtual const char* getName() const override;
			
			PhysXSubsystem* physx_subsystem;
			
		};
	}
}