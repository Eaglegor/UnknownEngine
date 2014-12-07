#pragma once

#include <LogManager.h>
#include <Logging.h>
#include <LogManager_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		class LogHelper : public ILogger
		{
		public:
			LOGMANAGER_EXPORT
			LogHelper(const std::string& name);

			LOGMANAGER_EXPORT
			LogHelper(const std::string& name, Core::LogSeverity log_level);

			LOGMANAGER_EXPORT
			~LogHelper();
			
			LOGMANAGER_EXPORT
			void init(Core::LogSeverity log_level);

			LOGMANAGER_EXPORT
			virtual const char* getName() const;
			
			LOGMANAGER_EXPORT
			ILogger* operator->()
			{
				return logger;
			}
			
			LOGMANAGER_EXPORT
			operator bool()
			{
				return logger != nullptr;
			}
			
			LOGMANAGER_EXPORT
			virtual void log ( const ILogRecord& log_record );
			
		private:
			const std::string name;
			ILogger* logger;
		};
	}
}