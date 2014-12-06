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
			SimpleLogRecord(Utils::LogSeverity severity, const std::string& text):
			text(text),
			severity(severity)
			{
			}
			
			virtual Utils::LogSeverity getSeverity() const override
			{
				return severity;
			}
			
			virtual const char* toString() const override
			{
				return text.c_str();
			}
			
		private:
			std::string text;
			Utils::LogSeverity severity;
		};
	}
}