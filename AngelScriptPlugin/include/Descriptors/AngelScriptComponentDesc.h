#pragma once

#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		struct AngelScriptComponentDesc
		{
			Utils::LogSeverity log_level = Utils::LogSeverity::NONE;
		};
	}
}