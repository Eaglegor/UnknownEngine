#pragma once

#include <LogManager_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		LOGMANAGER_EXPORT
		enum class LogSeverity : int
		{
		    NONE = 0,
		    ERROR2 = 1,
		    WARNING = 2,
		    INFO = 3,
		    DEBUG = 4
		};
	}
}
