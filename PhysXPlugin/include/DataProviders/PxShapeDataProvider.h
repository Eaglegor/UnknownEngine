#pragma once

#include <ResourceManager/DataProviders/LazyLoadDataProvider.h>
#include <memory>

namespace UnknownEngine
{
	namespace Physics
	{

		class PhysXSubsystem;
		class PxShapeOrientedWrapper;
		
		class PxShapeDataProvider : public Core::LazyLoadDataProvider
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