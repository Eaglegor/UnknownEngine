#pragma once

#include <ILogRecord.h>
#include <string>

namespace UnknownEngine
{
	namespace Core
	{
		class SimpleLogRecord : public ILogRecord
		{
		public:
			SimpleLogRecord(Core::LogSeverity severity, const std::string& text):
			text(text),
			severity(severity)
			{
			}
			
			virtual Core::LogSeverity getSeverity() const override
			{
				return severity;
			}
			
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