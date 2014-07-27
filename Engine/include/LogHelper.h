#pragma once

#include <ExportedMessages/LogMessage.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine
{
	namespace Core
	{

		class LogHelper
		{
			public:
				LogHelper ( const std::string &name, const LogMessage::Severity& log_level, EngineContext* engine_context )
					: packer ( MessageSystemParticipantId ( name ) ),
					  log_level ( log_level ),
					  message_dispatcher ( engine_context->getMessageDispatcher() )
				{}

				void log ( const LogMessage::Severity& severity, const std::string& message )
				{
					if ( severity > log_level ) return;
					LogMessage msg;
					msg.severity = severity;
					msg.log_entry = message;
					message_dispatcher->deliverMessage ( packer.packMessage ( msg ) );
				}

				void operator()(const LogMessage::Severity& severity, const std::string &message)
				{
				    log(severity, message);
				}
				
			private:
				LogMessagePacker packer;
				LogMessage::Severity log_level;
				MessageDispatcher *message_dispatcher;
		};

		#define LOG_INFO(log_helper, e) if(log_helper) log_helper->log(Core::LogMessage::LOG_SEVERITY_INFO, e);
		#define LOG_WARNING(log_helper, e) if(log_helper) log_helper->log(Core::LogMessage::LOG_SEVERITY_WARNING, e);
		#define LOG_ERROR(log_helper, e) if(log_helper) log_helper->log(Core::LogMessage::LOG_SEVERITY_ERROR, e);
		#define LOG_DEBUG(log_helper, e) if(log_helper) log_helper->log(Core::LogMessage::LOG_SEVERITY_DEBUG, e);
		
	}
}