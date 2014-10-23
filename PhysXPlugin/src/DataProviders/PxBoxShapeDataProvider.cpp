#include <DataProviders/PxBoxShapeDataProvider.h>
#include <DataProviders/PxMaterialDataProvider.h>
#include <PhysXSubsystem.h>
#include <Components/PxShapeOrientedWrapper.h>

using std::isfinite;

#include <geometry/PxBoxGeometry.h>
#include <PxPhysics.h>

namespace UnknownEngine
{
	namespace Physics
	{
		PxBoxShapeDataProvider::PxBoxShapeDataProvider ( const std::string& name, const PxBoxShapeDataProviderDesc& desc, PhysXSubsystem* physx_subsystem ):
		PxShapeDataProvider(name, physx_subsystem),
		desc(desc)
		{

		}
		
		const Loader::DataProviderType PxBoxShapeDataProvider::getType()
		{
			return PX_BOX_SHAPE_DATA_PROVIDER_TYPE;
		}

		void PxBoxShapeDataProvider::internalLoad ( Loader::ResourceContainer& out_container )
		{
			physx::PxBoxGeometry box_geometry(desc.width, desc.height, desc.depth);
			internal_shape.reset( new PxShapeOrientedWrapper(box_geometry, desc.material->getPxMaterial(), desc.pose_offset, physx_subsystem) );
			out_container.setData<PxShapeOrientedWrapper*>(internal_shape.get());
		}

		PxBoxShapeDataProvider::~PxBoxShapeDataProvider()
		{
		}
		
	}
}