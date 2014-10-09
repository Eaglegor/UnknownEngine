#pragma once

#include <DataProviders/PxBoxGeometryDataProvider.h>
#include <LogHelper.h>
#include <geometry/PxBoxGeometry.h>

namespace UnknownEngine
{
	namespace Physics
	{
		PxBoxGeometryDataProvider::PxBoxGeometryDataProvider(const std::string& name, const PxBoxGeometryDataProviderDesc &desc, Core::EngineContext* engine_context) :
			LazyLoadDataProvider(name),
			desc(desc)
		{
		}

		const Loader::DataProviderType& PxBoxGeometryDataProvider::getType()
		{
			return PX_BOX_GEOMETRY_DATA_PROVIDER_TYPE_NAME;
		}

		void PxBoxGeometryDataProvider::internalLoad(Loader::ResourceContainer& out_container)
		{
			out_container.setData<physx::PxBoxGeometry>( physx::PxBoxGeometry(desc.width, desc.height, desc.depth) );
		}
	}
}