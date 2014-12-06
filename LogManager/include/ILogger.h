#pragma once
#include <LogSeverity.h>
#include <ILogRecord.h>
#include <LogManager_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ILogger
		{
		public:
			LOGMANAGER_EXPORT
			virtual void log(const ILogRecord& log_record) = 0;

			LOGMANAGER_EXPORT
			virtual const char* getName() const = 0;

			LOGMANAGER_EXPORT
			virtual ~ILogger(){}
		};
	}
}