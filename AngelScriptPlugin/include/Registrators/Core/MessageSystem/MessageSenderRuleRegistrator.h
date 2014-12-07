#pragma once

#include <Registrators/ClassValueTypeRegistrator.h>
#include <MessageSystem/Policies/Sender/MessageSenderRules.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class MessageSenderRuleRegistrator : public ClassValueTypeRegistrator<Core::MessageSenderRule>
		{
		public:
			MessageSenderRuleRegistrator():
			ClassValueTypeRegistrator< Core::MessageSenderRule >("MessageSenderRule", CORE_AS_NAMESPACE_NAME)
			{};
			
			virtual bool registerProperties ( asIScriptEngine* script_engine ) const
			{
				int result;
				result = script_engine->RegisterObjectProperty(getRegisteredName(), "std::string message_type_name", asOFFSET(Core::MessageSenderRule, message_type_name));
				if(result < 0) return false;
				
				result = script_engine->RegisterObjectProperty(getRegisteredName(), "std::string delivery_policy_type_name", asOFFSET(Core::MessageSenderRule, delivery_policy_type_name));
				if(result < 0) return false;
				
				result = script_engine->RegisterObjectProperty(getRegisteredName(), "Core::Properties delivery_policy_options", asOFFSET(Core::MessageSenderRule, delivery_policy_options));
				if(result < 0) return false;
				
				return true;
			}
			
		};
	}
}