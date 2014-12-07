#pragma once
#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class MessageListenerRulesRegistrator : public ClassValueTypeRegistrator<Core::MessageListenerRules>
		{
		public:
			MessageListenerRulesRegistrator():
			ClassValueTypeRegistrator< Core::MessageListenerRules >("MessageListenerRules", CORE_AS_NAMESPACE_NAME)
			{}
			
			static void push_back(Core::MessageListenerRules* this_ptr, const Core::MessageListenerRule &rule)
			{
				this_ptr->push_back(rule);
			}
			
			virtual bool registerMethods ( asIScriptEngine* script_engine ) const override
			{
				int result;
				result = script_engine->RegisterObjectMethod(getRegisteredName(), "void push_back(const Core::MessageListenerRule& in)", asFUNCTION(MessageListenerRulesRegistrator::push_back), asCALL_CDECL_OBJFIRST);
				if(result < 0) return false;
				
				return true;
			}
		};
	}
}