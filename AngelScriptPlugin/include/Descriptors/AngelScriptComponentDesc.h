#pragma once

#include <LogSeverity.h>
#include <string>

namespace UnknownEngine
{
	namespace Behavior
	{
		struct AngelScriptComponentDesc
		{
			Utils::LogSeverity log_level = Utils::LogSeverity::NONE;
			std::string script_filename;
		};
	}
}