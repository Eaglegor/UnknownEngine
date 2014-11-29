#pragma once

#include <Registrators/Core/ASNamespaceName.h>
#include "ReceivedMessageDescWrapper.h"
#include <Registrators/ClassValueTypeRegistrator.h>
#include <MessageSystem/MessageListenerDesc.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ReceivedMessageDescRegistrator : public ClassValueTypeRegistrator<Core::ReceivedMessageDesc>
		{
		public:
			ReceivedMessageDescRegistrator ():
			ClassValueTypeRegistrator< Core::ReceivedMessageDesc >("ReceivedMessageDesc", CORE_AS_NAMESPACE_NAME)
			{}
			
			virtual bool registerProperties ( asIScriptEngine* script_engine ) const override
			{
				int result;
				result = script_engine->RegisterObjectProperty(getRegisteredName(), "std::string message_type_name", asOFFSET(Core::ReceivedMessageDesc, message_type_name));
				if(result < 0) return false;
				
				result = script_engine->RegisterObjectMethod(getRegisteredName(), "void set_receive_policy(Core::ReceivedMessageDesc::ReceivePolicyDesc &in)", asFUNCTION(ReceivedMessageDescWrapper::set_receive_policy), asCALL_CDECL_OBJFIRST);
				if(result < 0) return false;
				
				return true;
			}
		};
	}
}