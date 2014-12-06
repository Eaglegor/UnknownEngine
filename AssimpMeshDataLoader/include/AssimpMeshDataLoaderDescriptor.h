#pragma once
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Loader
	{
		struct AssimpMeshDataLoaderDescriptor
		{
			Core::LogSeverity log_level;
			
			AssimpMeshDataLoaderDescriptor():
			log_level(Core::LogSeverity::NONE)
			{}
		};
	}
}