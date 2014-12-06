#pragma once

#include <LogManager.h>
#include <SimpleLogRecord.h>
#include <InlineSpecification.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/trim.hpp>

#define DONT_APPEND_LINE_NUMBER
#define APPEND_LINE_NUMBER + "\n" + __FILE__ + " : " + std::to_string(__LINE__)

#ifndef ERROR_LINE_NUMBER 
	#define ERROR_LINE_NUMBER DONT_APPEND_LINE_NUMBER
#endif

#ifndef WARNING_LINE_NUMBER 
	#define WARNING_LINE_NUMBER DONT_APPEND_LINE_NUMBER
#endif

#ifndef INFO_LINE_NUMBER 
	#define INFO_LINE_NUMBER DONT_APPEND_LINE_NUMBER
#endif

#ifndef DEBUG_LINE_NUMBER 
	#define DEBUG_LINE_NUMBER DONT_APPEND_LINE_NUMBER
#endif

#define LOG_INFO(logger, message) if(logger) logger->log( Core::SimpleLogRecord(Utils::LogSeverity::INFO, std::string(message) INFO_LINE_NUMBER ) )
#define LOG_ERROR(logger, message) if(logger) logger->log( Core::SimpleLogRecord(Utils::LogSeverity::ERROR2, std::string(message) ERROR_LINE_NUMBER ) )
#define LOG_WARNING(logger, message) if(logger) logger->log( Core::SimpleLogRecord(Utils::LogSeverity::WARNING, std::string(message) WARNING_LINE_NUMBER ) )
#define LOG_DEBUG(logger, message) if(logger) logger->log( Core::SimpleLogRecord(Utils::LogSeverity::DEBUG, std::string(message) DEBUG_LINE_NUMBER ) )

namespace UnknownEngine
{
	UNKNOWNENGINE_INLINE
   	Core::ILogger* CREATE_LOGGER(const std::string& name, Utils::LogSeverity log_level)
	{
		return Core::LogManager::getSingleton()->getLogger(name.c_str(), log_level);
	}
	
	UNKNOWNENGINE_INLINE
	void RELEASE_LOGGER(Core::ILogger* logger)
	{
		if(logger) Core::LogManager::getSingleton()->releaseLogger(logger->getName());
	}
}


namespace boost
{
	template<>
	UNKNOWNENGINE_INLINE
	UnknownEngine::Utils::LogSeverity lexical_cast<UnknownEngine::Utils::LogSeverity, std::string>(const std::string &value)
	{
		std::string converted_value = value;
		boost::to_lower(converted_value);
		boost::trim(converted_value);
		if(converted_value=="info") return UnknownEngine::Utils::LogSeverity::INFO;
		if(converted_value=="debug") return UnknownEngine::Utils::LogSeverity::DEBUG;
		if(converted_value=="warning") return UnknownEngine::Utils::LogSeverity::WARNING;
		if(converted_value=="error") return UnknownEngine::Utils::LogSeverity::ERROR2;
		return UnknownEngine::Utils::LogSeverity::NONE;
	}
}