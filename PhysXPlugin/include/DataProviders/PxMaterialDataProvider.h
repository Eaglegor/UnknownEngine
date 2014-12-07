#pragma once

#include <ResourceManager/DataProviders/LazyLoadDataProvider.h>
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
		
		const Core::DataProviderType PX_MATERIAL_DATA_PROVIDER_TYPE = Core::DataProviderType("Loader.PxMaterial.PxMaterialDataProvider");
		
		class PxMaterialDataProvider : public Core::LazyLoadDataProvider
		{
		public:
			PxMaterialDataProvider(const std::string& name, const PxMaterialDataProviderDesc& desc, PhysXSubsystem* physx_subsystem);
			
			virtual const Core::DataProviderType getType() const override;
			virtual void internalLoad ( Core::ResourceContainer& out_container ) override;
			virtual void internalUnload ( Core::ResourceContainer& container ) override;
			
			physx::PxMaterial* getPxMaterial();
			
		private:
			PxMaterialDataProviderDesc desc;
			PhysXSubsystem* physx_subsystem;
			
		};
	}
}