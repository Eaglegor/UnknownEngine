#pragma once

#include <DataProviders/PxShapeDataProvider.h>
#include <Descriptors/DataProviders/PxBoxShapeDataProviderDesc.h>
#include <memory>
#include <AlignedNew.h>

namespace UnknownEngine
{
	namespace Physics
	{

		class PhysXSubsystem;
		class PxShapeOrientedWrapper;
		
		const Core::DataProviderType PX_BOX_SHAPE_DATA_PROVIDER_TYPE = Core::DataProviderType("Loader.PxShape.PxBoxShapeDataProvider");
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) PxBoxShapeDataProvider : public PxShapeDataProvider
		{
		public:
			PxBoxShapeDataProvider(const std::string &name, const PxBoxShapeDataProviderDesc& desc, PhysXSubsystem* physx_subsystem);
			~PxBoxShapeDataProvider();
			
			virtual const Core::DataProviderType getType() const override;
			virtual void internalLoad ( Core::ResourceContainer& out_container ) override;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

		private:
			PxBoxShapeDataProviderDesc desc;
			
		};
	}
}