#pragma once

#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		struct AngelScriptSubsystemDesc
		{
			Core::LogSeverity log_level;
			
			AngelScriptSubsystemDesc():
			log_level(Core::LogSeverity::DEBUG)
			{}
		};
	}
}