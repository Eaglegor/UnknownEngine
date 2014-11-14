#pragma once

#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		struct SimpleBehaviorsPluginDesc
		{
			Utils::LogSeverity log_level;
			
			SimpleBehaviorsPluginDesc():
			log_level(Utils::LogSeverity::NONE)
			{}
		};
	}
}