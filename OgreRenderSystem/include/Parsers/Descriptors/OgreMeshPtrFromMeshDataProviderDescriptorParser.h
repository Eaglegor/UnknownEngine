#pragma once

#include <Properties/Properties_fwd.h>
#include <Descriptors/DataProviders/OgreMeshPtrFromMeshDataProviderDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreMeshPtrFromMeshDataProviderDescriptorParser
		{
		public:
			static OgreMeshPtrFromMeshDataProviderDescriptor parse(const Core::Properties& props);
		};
	}
}