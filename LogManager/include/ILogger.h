#pragma once
#include <LogSeverity.h>
#include <ILogRecord.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ILogger
		{
		public:
			virtual void log(const ILogRecord& log_record) = 0;
			virtual const char* getName() const = 0;
			virtual ~ILogger(){}
		};
	}
}