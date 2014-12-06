#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Core
	{
		LogHelper::LogHelper ( const std::string& name ) :
		name ( name ),
		logger ( nullptr )
		{
		}

		LogHelper::LogHelper ( const std::string& name, Utils::LogSeverity log_level ) :
		name(name),
		logger(nullptr)
		{
			init(log_level);
		}

		LogHelper::~LogHelper()
		{
			RELEASE_LOGGER(logger);
		}
		
		void LogHelper::init ( Utils::LogSeverity log_level )
		{
			logger = CREATE_LOGGER(getName(), log_level);
		}
		
		const char* LogHelper::getName() const
		{
			return name.c_str();
		}

		void LogHelper::log ( const ILogRecord& log_record )
		{
			if(logger) logger->log(log_record);
		}
	}
}
#include <LogHelper.h>
