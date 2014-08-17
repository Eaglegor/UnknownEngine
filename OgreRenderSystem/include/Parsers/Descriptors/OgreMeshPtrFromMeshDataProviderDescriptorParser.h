#pragma once

#include <DataProviders/OgreMeshPtrFromMeshDataProvider.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreMeshPtrFromMeshDataProviderDescriptorParser
		{
		public:
			static OgreMeshPtrFromMeshDataProvider::Descriptor parse(const Core::Properties& props);
		};
	}
}