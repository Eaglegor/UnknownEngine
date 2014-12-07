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
			LOGMANAGER_EXPORT
			void addLoggingSubsystem(ILoggingSubsystem* logging_subsystem);

			LOGMANAGER_EXPORT
			void removeLoggingSubsystem(ILoggingSubsystem* logging_subsystem);

			LOGMANAGER_EXPORT
			ILogger* getLogger(const char* name, Core::LogSeverity log_level);

			LOGMANAGER_EXPORT
			void releaseLogger(const char* name);

		private:
			typedef std::mutex LockPrimitive;
			LockPrimitive lock;
			
			struct ProxyLoggerWrapper
			{
				ProxyLogger logger;
				size_t ref_counter = 1;
				
				ProxyLoggerWrapper(const char* name, Core::LogSeverity log_level):
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
		extern template class LOGMANAGER_EXPORT Singleton<LogManager>;
	#endif
#endif
		
	}
}