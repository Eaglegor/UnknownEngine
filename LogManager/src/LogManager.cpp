#include <LogManager.h>

namespace UnknownEngine
{
	namespace Core
	{
		template<>
		LogManager* Singleton<LogManager>::instance = nullptr;
		
		void LogManager::addLoggingSubsystem ( ILoggingSubsystem* logging_subsystem )
		{
			std::lock_guard<LockPrimitive> guard(lock);
			
			logging_subsystems.emplace(std::string(logging_subsystem->getName()), logging_subsystem);
			
			for(auto &iter : proxy_loggers)
			{
				iter.second.logger.addSubsystem(logging_subsystem);
			}
		}

		void LogManager::removeLoggingSubsystem ( ILoggingSubsystem* logging_subsystem )
		{
			std::lock_guard<LockPrimitive> guard(lock);
			
			for(auto &iter : proxy_loggers)
			{
				iter.second.logger.removeSubsystem(logging_subsystem);
			}
			
			logging_subsystems.erase(std::string(logging_subsystem->getName()));
		}

		ILogger* LogManager::getLogger ( const char* name, Core::LogSeverity log_level )
		{
			std::lock_guard<LockPrimitive> guard(lock);
			
			if(log_level == Core::LogSeverity::NONE) return nullptr;
			auto iter = proxy_loggers.find(std::string(name));
			if(iter != proxy_loggers.end()) 
			{
				++iter->second.ref_counter;
				return &iter->second.logger;
			}
			
			ProxyLogger& logger =  proxy_loggers.emplace( std::string(name), ProxyLoggerWrapper(name, log_level)).first->second.logger;
			for(auto &iter : logging_subsystems)
			{
				logger.addSubsystem(iter.second);
			}
			return &logger;
		}

		void LogManager::releaseLogger ( const char* name )
		{
			std::lock_guard<LockPrimitive> guard(lock);
			
			auto iter = proxy_loggers.find(std::string(name));
			if(iter == proxy_loggers.end()) return;
			
			if(--iter->second.ref_counter > 0) return;
			
			ProxyLogger& logger = iter->second.logger;
			for(auto &iter : logging_subsystems)
			{
				logger.removeSubsystem(iter.second);
			}
			proxy_loggers.erase(iter);
			
		}
	}
}