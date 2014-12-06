#pragma once

#include <ILoggingSubsystem.h>
#include <Logging/ConsoleLogger.h>
#include <mutex>

namespace UnknownEngine
{
	namespace Core
	{
		class ConsoleLoggingSubsystem : public Core::ILoggingSubsystem
		{
		public:
			ConsoleLoggingSubsystem(const char* name);
			
			virtual Core::ILogger* createLogger ( const char* name, Utils::LogSeverity log_level );
			virtual void destroyLogger ( ILogger* logger );
			virtual const char* getName();
			
			void write(const char* text);
			
		private:
			typedef std::mutex LockPrimitive;
			LockPrimitive mutex;
			
			std::string name;
		};
	}
}