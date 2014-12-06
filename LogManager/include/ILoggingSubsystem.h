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
			virtual ILogger* createLogger(const char* name, Core::LogSeverity log_level) = 0;
			virtual void destroyLogger(ILogger* logger) = 0;
			virtual const char* getName() = 0;
			virtual ~ILoggingSubsystem(){}
		};
	}
}