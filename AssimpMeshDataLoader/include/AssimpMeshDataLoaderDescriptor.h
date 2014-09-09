#pragma once
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Loader
	{
		struct AssimpMeshDataLoaderDescriptor
		{
			Core::LogMessage::Severity log_level;
			
			AssimpMeshDataLoaderDescriptor():
			log_level(Core::LogMessage::Severity::LOG_SEVERITY_NONE)
			{}
		};
	}
}