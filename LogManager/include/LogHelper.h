#pragma once

#include <LogManager.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Core
	{
		class LogHelper : public ILogger
		{
		public:
			LogHelper(const std::string& name);
			LogHelper(const std::string& name, Core::LogSeverity log_level);
			~LogHelper();
			
			void init(Core::LogSeverity log_level);
			virtual const char* getName() const;
			
			ILogger* operator->()
			{
				return logger;
			}
			
			operator bool()
			{
				return logger;
			}
			
			virtual void log ( const ILogRecord& log_record );
			
		private:
			const std::string name;
			ILogger* logger;
		};
	}
}