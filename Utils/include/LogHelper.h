#pragma once

#include <ExportedMessages/LogMessage.h>
#include <MessageSystem/MessageSender.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <EngineContext.h>
#include <InlineSpecification.h>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine
{
	namespace Utils
	{

		class LogHelper
		{
			public:
				LogHelper ( const std::string &name, const LogSeverity& minimal_severity, Core::EngineContext* engine_context )
					: message_sender ( name, engine_context ),
					  minimal_severity ( minimal_severity )
				{}

				void log ( const LogSeverity& severity, const std::string& message )
				{
					if ( severity > minimal_severity ) return;
					LogMessage msg;
					msg.sender_info = message_sender.getName();
					msg.severity = severity;
					msg.log_entry = message;
					message_sender.sendMessage(msg);
				}

				void operator() ( const LogSeverity& severity, const std::string &message )
				{
					log ( severity, message );
				}

				UNKNOWNENGINE_INLINE
				void setMinimalSeverity ( const LogSeverity& minimal_severity )
				{
					this->minimal_severity = minimal_severity;
				}

				static LogSeverity parseLogLevel ( const std::string& log_level_name )
				{
					std::string lower_case_level = log_level_name;
					boost::to_lower(lower_case_level);
					boost::trim(lower_case_level);
					if ( lower_case_level == "info" ) return LogSeverity::INFO;
					if ( lower_case_level == "warning" ) return LogSeverity::WARNING;
					if ( lower_case_level == "error" ) return LogSeverity::ERROR2;
					if ( lower_case_level == "debug" ) return LogSeverity::DEBUG;
					return LogSeverity::NONE;
				}

			private:
				Core::MessageSender<LogMessage> message_sender;
				LogSeverity minimal_severity;
		};

// We use define to be able to completely delete some log messages in release versions to increase performance
#define LOG_INFO(log_helper, e) if(log_helper) log_helper->log(Utils::LogSeverity::INFO, e);
#define LOG_WARNING(log_helper, e) if(log_helper) log_helper->log(Utils::LogSeverity::WARNING, e);
#define LOG_ERROR(log_helper, e) if(log_helper) log_helper->log(Utils::LogSeverity::ERROR2, e);
#define LOG_DEBUG(log_helper, e) if(log_helper) log_helper->log(Utils::LogSeverity::DEBUG, e);

	}
}

namespace boost
{
	typedef UnknownEngine::Utils::LogSeverity UnknownEngineLogSeverity;
	
	template<>
	UNKNOWNENGINE_INLINE
	UnknownEngineLogSeverity lexical_cast<UnknownEngineLogSeverity, std::string>(const std::string& string_value)
	{
		return UnknownEngine::Utils::LogHelper::parseLogLevel(string_value);
	}
}
