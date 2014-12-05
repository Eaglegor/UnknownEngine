#pragma once
#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ILogger;

		class ILoggingSubsystem
		{
		public:
			virtual ILogger* getLogger(const char* name, Utils::LogSeverity log_level) = 0;
			virtual void releaseLogger(const char* name) = 0;
			virtual const char* getName() = 0;
			virtual ~ILoggingSubsystem(){}
		};
	}
}