#include <DataProviders/PxMaterialDataProvider.h>
#include <EngineContext.h>
#include <PhysXSubsystem.h>

using std::isfinite;

#include <PxPhysics.h>
#include <PxMaterial.h>

namespace UnknownEngine
{
	namespace Physics
	{
		PxMaterialDataProvider::PxMaterialDataProvider ( const std::string& name, const PxMaterialDataProviderDesc& desc, PhysXSubsystem *physx_subsystem ):
		LazyLoadDataProvider ( name ),
		desc(desc),
		physx_subsystem(physx_subsystem)
		{
		}
		
		const Loader::DataProviderType PxMaterialDataProvider::getType()
		{
			return PX_MATERIAL_DATA_PROVIDER_TYPE;
		}

		void PxMaterialDataProvider::internalLoad ( Loader::ResourceContainer& out_container )
		{
			physx::PxMaterial* material = physx_subsystem->getPxPhysics()->createMaterial(desc.static_friction, desc.dynamic_friction, desc.restitution);
			out_container.setData<physx::PxMaterial*>(material);
		}
		
		void PxMaterialDataProvider::internalUnload ( Loader::ResourceContainer& container )
		{
			
			physx::PxMaterial* material = container.getData<physx::PxMaterial*>();
			material->release();
		}
		
		physx::PxMaterial* PxMaterialDataProvider::getPxMaterial()
		{
			return getResource().getData<physx::PxMaterial*>();
		}

	}
}