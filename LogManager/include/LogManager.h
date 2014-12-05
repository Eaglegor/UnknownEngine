#pragma once

#include <unordered_map>
#include <ILoggingSubsystem.h>
#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ProxyLogger;
		class ILogger;

		class LogManager
		{
		public:
			void addLoggingSubsystem(ILoggingSubsystem* logging_subsystem);
			void removeLoggingSubsystem(ILoggingSubsystem* logging_subsystem);

			ILogger* getLogger(const char* name, Utils::LogSeverity log_level);
			void releaseLogger(const char* name);

		private:
			std::unordered_map<std::string, ProxyLogger*> proxy_loggers;
			std::unordered_map<std::string, ILoggingSubsystem*> logging_subsystems;
		};
	}
}