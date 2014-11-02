#pragma once
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Loader
	{
		struct AssimpMeshDataLoaderDescriptor
		{
			Utils::LogSeverity log_level;
			
			AssimpMeshDataLoaderDescriptor():
			log_level(Utils::LogSeverity::NONE)
			{}
		};
	}
}