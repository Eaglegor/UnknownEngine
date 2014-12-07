#pragma once
#include <ResourceManager/DataProviders/BaseDataProviderFactory.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PxMaterialDataProvider;
		class PhysXSubsystem;
		
		class PxMaterialDataProvidersFactory : public Core::BaseDataProviderFactory
		{
		public:
			PxMaterialDataProvidersFactory(PhysXSubsystem *physx_subsystem);
			
		private:
			Core::IDataProvider* createPxMaterialDataProvider(const Core::DataProviderDesc& desc);
			
			virtual const char* getName() const override;
			
			PhysXSubsystem* physx_subsystem;
			
		};
	}
}