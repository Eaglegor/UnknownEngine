#pragma once

#include <unordered_map>
#include <ILoggingSubsystem.h>
#include <LogSeverity.h>
#include <Singleton.h>
#include <ProxyLogger.h>
#include <LogManager_export.h>
#include <mutex>

namespace UnknownEngine
{
	namespace Core
	{
		class ProxyLogger;
		class ILogger;

		class LogManager : public Singleton<LogManager>
		{
		public:
			void addLoggingSubsystem(ILoggingSubsystem* logging_subsystem);
			void removeLoggingSubsystem(ILoggingSubsystem* logging_subsystem);

			ILogger* getLogger(const char* name, Utils::LogSeverity log_level);
			void releaseLogger(const char* name);

		private:
			typedef std::mutex LockPrimitive;
			LockPrimitive lock;
			
			struct ProxyLoggerWrapper
			{
				ProxyLogger logger;
				size_t ref_counter = 1;
				
				ProxyLoggerWrapper(const char* name, Utils::LogSeverity log_level):
				logger(name, log_level)
				{}
			};
			
			std::unordered_map<std::string, ProxyLoggerWrapper> proxy_loggers;
			std::unordered_map<std::string, ILoggingSubsystem*> logging_subsystems;
		};
		
#ifdef _MSC_VER
	#ifdef LogManager_EXPORTS
		template class LOGMANAGER_EXPORT Singleton<LogManager>;
	#else
		template extern class LOGMANAGER_EXPORT Singleton<LogManager>;
	#endif
#endif
		
	}
}