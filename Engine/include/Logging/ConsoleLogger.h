#pragma once

#include <ILogger.h>
#include <string>

namespace UnknownEngine
{
	namespace Core
	{

		class ConsoleLoggingSubsystem;
		class ConsoleLogger : public Core::ILogger
		{
		public:
			ConsoleLogger(const char* name, Utils::LogSeverity log_level, ConsoleLoggingSubsystem* logging_subsystem);
			virtual const char* getName() const override;
			virtual void log ( const ILogRecord& log_record ) override;
			
		private:
			const std::string name;
			Utils::LogSeverity log_level;
			ConsoleLoggingSubsystem* logging_subsystem;
		};
	}
}