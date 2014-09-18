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
	namespace Core
	{

		class LogHelper
		{
			public:
				LogHelper ( const std::string &name, const LogMessage::Severity& minimal_severity, EngineContext* engine_context )
					: message_sender ( MessageSystemParticipantId ( name ), engine_context ),
					  minimal_severity ( minimal_severity )
				{}

				void log ( const LogMessage::Severity& severity, const std::string& message )
				{
					if ( severity > minimal_severity ) return;
					LogMessage msg;
					msg.severity = severity;
					msg.log_entry = message;
					message_sender.sendMessage(msg);
				}

				void operator() ( const LogMessage::Severity& severity, const std::string &message )
				{
					log ( severity, message );
				}

				UNKNOWNENGINE_INLINE
				void setMinimalSeverity ( const LogMessage::Severity& minimal_severity )
				{
					this->minimal_severity = minimal_severity;
				}

				static LogMessage::Severity parseLogLevel ( const std::string& log_level_name )
				{
					std::string lower_case_level = log_level_name;
					boost::to_lower(lower_case_level);
					boost::trim(lower_case_level);
					if ( lower_case_level == "info" ) return LogMessage::Severity::LOG_SEVERITY_INFO;
					if ( lower_case_level == "warning" ) return LogMessage::Severity::LOG_SEVERITY_WARNING;
					if ( lower_case_level == "error" ) return LogMessage::Severity::LOG_SEVERITY_ERROR;
					if ( lower_case_level == "debug" ) return LogMessage::Severity::LOG_SEVERITY_DEBUG;
					return LogMessage::Severity::LOG_SEVERITY_NONE;
				}

			private:
				MessageSender<LogMessage> message_sender;
				LogMessage::Severity minimal_severity;
		};

#define LOG_INFO(log_helper, e) if(log_helper) log_helper->log(Core::LogMessage::Severity::LOG_SEVERITY_INFO, e);
#define LOG_WARNING(log_helper, e) if(log_helper) log_helper->log(Core::LogMessage::Severity::LOG_SEVERITY_WARNING, e);
#define LOG_ERROR(log_helper, e) if(log_helper) log_helper->log(Core::LogMessage::Severity::LOG_SEVERITY_ERROR, e);
#define LOG_DEBUG(log_helper, e) if(log_helper) log_helper->log(Core::LogMessage::Severity::LOG_SEVERITY_DEBUG, e);

	}
}

namespace boost
{
	typedef UnknownEngine::Core::LogMessage::Severity UnknownEngineLogSeverity;
	
	template<>
	UNKNOWNENGINE_INLINE
	UnknownEngineLogSeverity lexical_cast<UnknownEngineLogSeverity, std::string>(const std::string& string_value)
	{
		return UnknownEngine::Core::LogHelper::parseLogLevel(string_value);
	}
}
