#pragma once
#include <DataProviders/AssimpMeshDataProvider.h>
#include <Properties/Properties_fwd.h>

namespace UnknownEngine
{
	namespace Loader
	{
		class AssimpMeshDataProviderDescParser
		{
		public:
			static AssimpMeshDataProvider::Descriptor parse(const Core::Properties& props);
		};
	}
}