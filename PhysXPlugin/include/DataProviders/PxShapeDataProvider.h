#pragma once

#include <DataProvider/LazyLoadDataProvider.h>
#include <memory>

namespace UnknownEngine
{
	namespace Physics
	{

		class PhysXSubsystem;
		class PxShapeOrientedWrapper;
		
		class PxShapeDataProvider : public Loader::LazyLoadDataProvider
		{
		public:
			PxShapeDataProvider(const std::string &name, PhysXSubsystem* physx_subsystem);
			~PxShapeDataProvider();
			
			PxShapeOrientedWrapper* getPxShapeWrapper();

		protected:
			PhysXSubsystem* physx_subsystem;
			std::unique_ptr<PxShapeOrientedWrapper> internal_shape;
			
		};
	}
}