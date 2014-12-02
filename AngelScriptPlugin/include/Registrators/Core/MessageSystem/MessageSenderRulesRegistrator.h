#pragma once
#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>
#include <MessageSystem/MessageSenderRules.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class MessageSenderRulesRegistrator : public ClassValueTypeRegistrator<Core::MessageSenderRules>
		{
		public:
			MessageSenderRulesRegistrator():
			ClassValueTypeRegistrator< Core::MessageSenderRules >("MessageSenderRules", CORE_AS_NAMESPACE_NAME)
			{}
			
			static void push_back(Core::MessageSenderRules* this_ptr, const Core::MessageSenderRule& rule)
			{
				this_ptr->push_back(rule);
			}
			
			virtual bool registerMethods ( asIScriptEngine* script_engine ) const override
			{
				int result;
				result = script_engine->RegisterObjectMethod(getRegisteredName(), "void push_back(const Core::MessageSenderRule& in)", asFUNCTION(MessageSenderRulesRegistrator::push_back), asCALL_CDECL_OBJFIRST);
				if(result < 0) return false;
				
				return true;
			}
		};
	}
}