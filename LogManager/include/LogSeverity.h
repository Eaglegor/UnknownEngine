#pragma once

#include <LogManager_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		enum class LogSeverity : int
		{
		    NONE = 0,
		    ERROR = 1,
		    WARNING = 2,
		    INFO = 3,
		    DEBUG = 4
		};
	}
}
