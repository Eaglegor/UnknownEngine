#pragma once
#include <ResourceManager/DataProviders/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PxBoxShapeDataProvider;
		class PhysXSubsystem;
		
		class PxDataProvidersFactory : public Core::BaseDataProviderFactory
		{
		public:
			PxDataProvidersFactory();
			
			void setPhysXSubsystem(PhysXSubsystem* physx_subsystem);
			virtual const char* getName() const override {return "PhysX.DataProvidersFactory";}
			
		private:
			Core::IDataProvider* createPxBoxShapeDataProvider(const Core::DataProviderDesc& desc);
			
			Core::IDataProvider* createPxMaterialDataProvider(const Core::DataProviderDesc& desc);
			
			PhysXSubsystem* physx_subsystem;
			
		};
	}
}