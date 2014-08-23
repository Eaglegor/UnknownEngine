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

			Core::LogMessage::Severity log_level;

			OgreMeshPtrFromMeshDataProviderDescriptor() :
				mesh_data_provider ( nullptr ),
				log_level ( Core::LogMessage::Severity::LOG_SEVERITY_NONE )
			{}
		};
	}
}
