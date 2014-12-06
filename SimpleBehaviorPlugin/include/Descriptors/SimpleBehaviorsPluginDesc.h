#pragma once

#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		struct SimpleBehaviorsPluginDesc
		{
			Core::LogSeverity log_level;
			
			SimpleBehaviorsPluginDesc():
			log_level(Core::LogSeverity::NONE)
			{}
		};
	}
}