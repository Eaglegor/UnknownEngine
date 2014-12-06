#pragma once

#include <ILogger.h>
#include <string>
#include <unordered_map>
#include <mutex>

namespace UnknownEngine
{
	namespace Core
	{

		class ILoggingSubsystem;
		class ProxyLogger : public ILogger
		{
		public:
			ProxyLogger(const char* name, Utils::LogSeverity log_level):
				name(name),
				log_level(log_level)
			{}

			ProxyLogger(const ProxyLogger& logger):
			loggers(logger.loggers),
			name(logger.name),
			log_level(logger.log_level)
			{}
			
			virtual void log ( const ILogRecord& log_record ) override;
			virtual const char* getName() const override;
			virtual void addSubsystem(ILoggingSubsystem* logging_subsystem);
			virtual void removeSubsystem(ILoggingSubsystem* logging_subsystem);

		private:
			typedef std::mutex LockPrimitive;
			
			LockPrimitive mutex;
			std::unordered_map<std::string, ILogger*> loggers;
			std::string name;
			Utils::LogSeverity log_level;
		};
	}
}