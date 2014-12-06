#include <ProxyLogger.h>
#include <ILoggingSubsystem.h>

namespace UnknownEngine
{
	namespace Core
	{
		const char* ProxyLogger::getName() const
		{
			return name.c_str();
		}
		
		void ProxyLogger::addSubsystem ( ILoggingSubsystem* logging_subsystem )
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			
			ILogger* logger = logging_subsystem->createLogger(getName(), log_level);
			loggers.emplace(std::string(logging_subsystem->getName()), logger);
		}

		void ProxyLogger::removeSubsystem ( ILoggingSubsystem* logging_subsystem )
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			
			auto iter = loggers.find(logging_subsystem->getName());
			if(iter == loggers.end()) return;
			logging_subsystem->destroyLogger(iter->second);
			loggers.erase(iter);
		}
	
		void ProxyLogger::log ( const ILogRecord& log_record )
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			
			for(auto &iter : loggers)
			{
				if(iter.second != nullptr) iter.second->log(log_record);
			}
		}
	}
}