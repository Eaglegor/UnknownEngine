#include <Logging/ConsoleLogger.h>
#include <Logging/ConsoleLoggingSubsystem.h>
#include <iostream>

namespace UnknownEngine
{
	namespace Core
	{
		ConsoleLogger::ConsoleLogger ( const char* name, Utils::LogSeverity log_level, ConsoleLoggingSubsystem* logging_subsystem ):
		name(name),
		log_level(log_level),
		logging_subsystem(logging_subsystem)
		{
		}

		const char* ConsoleLogger::getName() const
		{
			return name.c_str();
		}

		void ConsoleLogger::log ( const ILogRecord& log_record )
		{
			Utils::LogSeverity severity = log_record.getSeverity();
			if(severity > log_level) return;
			
			std::string text;
			switch(severity)
			{
				case Utils::LogSeverity::DEBUG:
				{
					text = "[DEBUG] ";
					break;
				}
				case Utils::LogSeverity::ERROR2:
				{
					text = "[ERROR] ";
					break;
				}
				case Utils::LogSeverity::INFO:
				{
					text = "[INFO] ";
					break;
				}
				case Utils::LogSeverity::WARNING:
				{
					text = "[WARNING] ";
					break;
				}
			}
			text += getName();
			text += ": ";
			text += log_record.toString();
			
			logging_subsystem->write(text.c_str());
		}

	}
}