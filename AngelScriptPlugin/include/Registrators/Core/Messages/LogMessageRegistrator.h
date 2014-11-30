#pragma once

#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/PODTypeRegistrator.h>
#include <Registrators/Utils/ASNamespaceName.h>
#include <Registrators/Core/MessageSystem/MessageSenderRegistrator.h>
#include <Registrators/Core/MessageSystem/MessageListenerRegistrator.h>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class LogMessageRegistrator: public ClassValueTypeRegistrator<Utils::LogMessage >
		{
			public:
				LogMessageRegistrator() :
					ClassValueTypeRegistrator< Utils::LogMessage > ( "LogMessage", UTILS_AS_NAMESPACE_NAME )
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
