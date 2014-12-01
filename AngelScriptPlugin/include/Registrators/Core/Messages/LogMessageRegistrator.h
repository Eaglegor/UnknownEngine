#pragma once

#include <Registrators/PODTypeRegistrator.h>
#include <Registrators/Utils/ASNamespaceName.h>
#include <Registrators/Core/MessageSystem/MessageSenderRegistrator.h>
#include <Registrators/Core/MessageSystem/MessageListenerRegistrator.h>
#include <Registrators/MessageTypeRegistrator.h>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class LogMessageRegistrator: public MessageTypeRegistrator<Utils::LogMessage >
		{
			public:
				LogMessageRegistrator() :
					MessageTypeRegistrator< Utils::LogMessage > ( "LogMessage", UTILS_AS_NAMESPACE_NAME )
				{}
				
				virtual bool registerProperties ( asIScriptEngine* script_engine ) const override
				{
					int result;
					result = script_engine->RegisterObjectProperty(getRegisteredName(), "std::string log_entry", asOFFSET(Utils::LogMessage, log_entry));
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectProperty(getRegisteredName(), "std::string sender_info", asOFFSET(Utils::LogMessage, sender_info));
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectProperty(getRegisteredName(), "int severity", asOFFSET(Utils::LogMessage, severity));
					if(result < 0) return false;
					
					result = script_engine->RegisterEnum("LogSeverity");
					if(result < 0) return false;
					
					result = script_engine->RegisterEnumValue("LogSeverity", "NONE", static_cast<int>(Utils::LogSeverity::NONE));
					if(result < 0) return false;
					
					result = script_engine->RegisterEnumValue("LogSeverity", "INFO", static_cast<int>(Utils::LogSeverity::INFO));
					if(result < 0) return false;
					
					result = script_engine->RegisterEnumValue("LogSeverity", "ERROR", static_cast<int>(Utils::LogSeverity::ERROR2));
					if(result < 0) return false;
					
					result = script_engine->RegisterEnumValue("LogSeverity", "WARNING", static_cast<int>(Utils::LogSeverity::WARNING));
					if(result < 0) return false;
					
					result = script_engine->RegisterEnumValue("LogSeverity", "DEBUG", static_cast<int>(Utils::LogSeverity::DEBUG));
					if(result < 0) return false;
					
					return true;
				}
				
				virtual bool registerRelatedTypes ( asIScriptEngine* script_engine ) const override
				{
					return MessageSenderRegistrator<Utils::LogMessage>("Utils::LogMessage").registerType(script_engine) &&
					MessageListenerRegistrator<Utils::LogMessage>("Utils::LogMessage").registerType(script_engine);
				}
		};
	}
}
