#pragma once
#include <Registrators/ClassReferenceTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class MessageDispatcherRegistrator : public ClassReferenceTypeRegistrator<Core::MessageDispatcher>
		{
		public:
			MessageDispatcherRegistrator():
			ClassReferenceTypeRegistrator< Core::MessageDispatcher >("MessageDispatcher", CORE_AS_NAMESPACE_NAME)
			{}
			
			static void setListenerRules(Core::MessageDispatcher* this_ptr, const std::string& name, const Core::MessageListenerRules& rules)
			{
				this_ptr->setListenerRules(name.c_str(), rules);
			}
			
			static void setSenderRules(Core::MessageDispatcher* this_ptr, const std::string& name, const Core::MessageSenderRules& rules)
			{
				this_ptr->setSenderRules(name.c_str(), rules);
			}
			
			virtual bool registerMethods ( asIScriptEngine* script_engine ) const
			{
				int result;
				result = script_engine->RegisterObjectMethod(getRegisteredName(), "void setListenerRules(const std::string& in, const Core::MessageListenerRules& in)", asFUNCTION(MessageDispatcherRegistrator::setListenerRules), asCALL_CDECL_OBJFIRST);
				if(result < 0) return false;
				
				result = script_engine->RegisterObjectMethod(getRegisteredName(), "void setSenderRules(const std::string& in, const Core::MessageSenderRules& in)", asFUNCTION(MessageDispatcherRegistrator::setSenderRules), asCALL_CDECL_OBJFIRST);
				if(result < 0) return false;

				return true;
			}
		};
	}
}