#pragma once
#include <DataProvider/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PxMaterialDataProvider;
		class PhysXSubsystem;
		
		class PxMaterialDataProvidersFactory : public Loader::BaseDataProviderFactory
		{
		public:
			PxMaterialDataProvidersFactory(PhysXSubsystem *physx_subsystem);
			
		private:
			Loader::IDataProvider* createPxMaterialDataProvider(const Loader::DataProviderDesc& desc);
			
			virtual const char* getName() const override;
			
			PhysXSubsystem* physx_subsystem;
			
		};
	}
}