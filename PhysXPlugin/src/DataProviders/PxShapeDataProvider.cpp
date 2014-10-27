#include <DataProviders/PxShapeDataProvider.h>
#include <PhysXSubsystem.h>
#include <Components/PxShapeOrientedWrapper.h>

using std::isfinite;

#include <geometry/PxBoxGeometry.h>
#include <PxPhysics.h>

namespace UnknownEngine
{
	namespace Physics
	{
		PxShapeDataProvider::PxShapeDataProvider ( const std::string& name, PhysXSubsystem* physx_subsystem ):
		LazyLoadDataProvider ( name ),
		physx_subsystem(physx_subsystem)
		{
		}

		PxShapeOrientedWrapper* PxShapeDataProvider::getPxShapeWrapper()
		{
			return getResource().getData < PxShapeOrientedWrapper* >();
		}

		PxShapeDataProvider::~PxShapeDataProvider()
		{
		}
		
	}
}