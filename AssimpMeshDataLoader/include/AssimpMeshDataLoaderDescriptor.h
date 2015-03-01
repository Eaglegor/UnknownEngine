#pragma once
#include <LogSeverity.h>

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