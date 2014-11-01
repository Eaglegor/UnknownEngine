#pragma once

#include <ExportedMessages/LogMessage.h>
#include <DataProvider/IDataProvider.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		struct OgreMeshPtrFromMeshDataProviderDescriptor
		{
			Loader::IDataProvider* mesh_data_provider;

			Utils::LogSeverity log_level;

			OgreMeshPtrFromMeshDataProviderDescriptor() :
				mesh_data_provider ( nullptr ),
				log_level ( Utils::LogSeverity::NONE )
			{}
		};
	}
}
