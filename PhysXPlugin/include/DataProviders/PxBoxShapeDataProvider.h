#pragma once

#include <DataProvider/LazyLoadDataProvider.h>
#include <Descriptors/DataProviders/PxBoxShapeDataProviderDesc.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PhysXSubsystem;
		class PxShapeOrientedWrapper;
		
		const Loader::DataProviderType PX_BOX_SHAPE_DATA_PROVIDER_TYPE = Loader::DataProviderType("Loader.PxShape.PxBoxShapeDataProvider");
		
		class PxBoxShapeDataProvider : public Loader::LazyLoadDataProvider
		{
		public:
			PxBoxShapeDataProvider(const std::string &name, const PxBoxShapeDataProviderDesc& desc, PhysXSubsystem* physx_subsystem);
			~PxBoxShapeDataProvider();
			
			virtual const Loader::DataProviderType getType();
			virtual void internalLoad ( Loader::ResourceContainer& out_container );
			
		private:
			PxBoxShapeDataProviderDesc desc;
			PhysXSubsystem* physx_subsystem;
			std::unique_ptr<PxShapeOrientedWrapper> internal_shape;
			
		};
	}
}