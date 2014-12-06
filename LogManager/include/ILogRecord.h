#pragma once
#include <LogSeverity.h>
#include <LogManager_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ILogRecord
		{
		public:
			LOGMANAGER_EXPORT
			virtual Core::LogSeverity getSeverity() const = 0;

			LOGMANAGER_EXPORT
			virtual const char* toString() const = 0;
		};
	}
}