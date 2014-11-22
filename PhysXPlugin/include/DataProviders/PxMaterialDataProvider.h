#pragma once

#include <DataProvider/LazyLoadDataProvider.h>
#include <Descriptors/DataProviders/PxMaterialDataProviderDesc.h>

namespace physx
{
	class PxMaterial;
}

namespace UnknownEngine
{
	
	namespace Core
	{
		class EngineContext;
	}
	
	namespace Physics
	{
		
		class PhysXSubsystem;
		
		const Loader::DataProviderType PX_MATERIAL_DATA_PROVIDER_TYPE = Loader::DataProviderType("Loader.PxMaterial.PxMaterialDataProvider");
		
		class PxMaterialDataProvider : public Loader::LazyLoadDataProvider
		{
		public:
			PxMaterialDataProvider(const std::string& name, const PxMaterialDataProviderDesc& desc, PhysXSubsystem* physx_subsystem);
			
			virtual const Loader::DataProviderType getType() const override;
			virtual void internalLoad ( Loader::ResourceContainer& out_container ) override;
			virtual void internalUnload ( Loader::ResourceContainer& container ) override;
			
			physx::PxMaterial* getPxMaterial();
			
		private:
			PxMaterialDataProviderDesc desc;
			PhysXSubsystem* physx_subsystem;
			
		};
	}
}