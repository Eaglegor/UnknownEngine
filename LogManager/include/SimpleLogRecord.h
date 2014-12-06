#pragma once

#include <ILogRecord.h>
#include <string>
#include <LogManager_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		class SimpleLogRecord : public ILogRecord
		{
		public:
			LOGMANAGER_EXPORT
			SimpleLogRecord(Core::LogSeverity severity, const std::string& text):
			text(text),
			severity(severity)
			{
			}
			
			LOGMANAGER_EXPORT
			virtual Core::LogSeverity getSeverity() const override
			{
				return severity;
			}
			
			LOGMANAGER_EXPORT
			virtual const char* toString() const override
			{
				return text.c_str();
			}
			
		private:
			std::string text;
			Core::LogSeverity severity;
		};
	}
}