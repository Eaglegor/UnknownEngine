#pragma once
#include <LogSeverity.h>
#include <LogManager_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ILogger;

		class ILoggingSubsystem
		{
		public:
			LOGMANAGER_EXPORT
			virtual ILogger* createLogger(const char* name, Core::LogSeverity log_level) = 0;

			LOGMANAGER_EXPORT
			virtual void destroyLogger(ILogger* logger) = 0;

			LOGMANAGER_EXPORT
			virtual const char* getName() = 0;

			LOGMANAGER_EXPORT
			virtual ~ILoggingSubsystem(){}
		};
	}
}