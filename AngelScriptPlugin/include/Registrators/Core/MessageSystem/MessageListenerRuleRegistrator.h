#pragma once

#include <Registrators/ClassValueTypeRegistrator.h>
#include <MessageSystem/MessageListenerRules.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class MessageListenerRuleRegistrator : public ClassValueTypeRegistrator<Core::MessageListenerRule>
		{
		public:
			MessageListenerRuleRegistrator():
			ClassValueTypeRegistrator< Core::MessageListenerRule >("MessageListenerRule", CORE_AS_NAMESPACE_NAME)
			{};
			
			virtual bool registerProperties ( asIScriptEngine* script_engine ) const
			{
				int result;
				result = script_engine->RegisterObjectProperty(getRegisteredName(), "std::string message_type_name", asOFFSET(Core::MessageListenerRule, message_type_name));
				if(result < 0) return false;
				
				result = script_engine->RegisterObjectProperty(getRegisteredName(), "std::string receive_policy_type_name", asOFFSET(Core::MessageListenerRule, receive_policy_type_name));
				if(result < 0) return false;
				
				result = script_engine->RegisterObjectProperty(getRegisteredName(), "Core::Properties receive_policy_options", asOFFSET(Core::MessageListenerRule, receive_policy_options));
				if(result < 0) return false;
				
				return true;
			}
			
		};
	}
}