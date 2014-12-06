#pragma once

#include <LogSeverity.h>
#include <string>

namespace UnknownEngine
{
	namespace Behavior
	{
		struct AngelScriptComponentDesc
		{
			Core::LogSeverity log_level = Core::LogSeverity::NONE;
			std::string script_filename;
		};
	}
}