#include <Logging/ConsoleLoggingSubsystem.h>
#include <iostream>

namespace UnknownEngine
{
	namespace Core
	{
		ConsoleLoggingSubsystem::ConsoleLoggingSubsystem ( const char* name ):
		name(name)
		{
		}

		ILogger* ConsoleLoggingSubsystem::createLogger ( const char* name, Utils::LogSeverity log_level )
		{
			return new ConsoleLogger(name, log_level, this);
		}

		void ConsoleLoggingSubsystem::destroyLogger ( ILogger* logger )
		{
			if(logger) delete logger;
		}

		const char* ConsoleLoggingSubsystem::getName()
		{
			return name.c_str();
		}
		
		void ConsoleLoggingSubsystem::write ( const char* text )
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			std::cout << text << std::endl;
		}

	}
}