#pragma once

#include <ResourceManager/DataProviders/IDataProvider.h>
#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		struct OgreMeshPtrFromMeshDataProviderDescriptor
		{
			Core::IDataProvider* mesh_data_provider;

			Core::LogSeverity log_level;

			OgreMeshPtrFromMeshDataProviderDescriptor() :
				mesh_data_provider ( nullptr ),
				log_level ( Core::LogSeverity::NONE )
			{}
		};
	}
}
