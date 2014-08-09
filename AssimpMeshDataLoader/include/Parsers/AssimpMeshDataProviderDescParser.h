#pragma once
#include <DataProviders/AssimpMeshDataProvider.h>
#include <Properties/Properties.h>

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