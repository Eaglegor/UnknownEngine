#pragma once

#include <LogManager_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		enum class LogSeverity : int
		{
		    NONE = 0,
		    ERROR_ = 1, // "_" is to avoid wingdi32 ERROR macro. Damned microsoft.
		    WARNING = 2,
		    INFO = 3,
		    DEBUG = 4
		};
	}
}
