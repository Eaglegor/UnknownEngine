#pragma once

#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		struct AngelScriptSubsystemDesc
		{
			Utils::LogSeverity log_level;
			
			AngelScriptSubsystemDesc():
			log_level(Utils::LogSeverity::DEBUG)
			{}
		};
	}
}