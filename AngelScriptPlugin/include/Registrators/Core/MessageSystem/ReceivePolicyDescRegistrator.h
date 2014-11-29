#pragma once

#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>
#include <MessageSystem/MessageListenerDesc.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ReceivePolicyDescRegistrator : public ClassValueTypeRegistrator<Core::ReceivedMessageDesc::ReceivePolicyDesc>
		{
		public:
			ReceivePolicyDescRegistrator():
			ClassValueTypeRegistrator< UnknownEngine::Core::ReceivedMessageDesc::ReceivePolicyDesc >("ReceivePolicyDesc", CORE_AS_NAMESPACE_NAME + "::ReceivedMessageDesc")
			{}
			
			virtual bool registerProperties ( asIScriptEngine* script_engine ) const override
			{
				int result;
				result = script_engine->RegisterObjectProperty(getRegisteredName(), "std::string receive_policy_type_name", asOFFSET(Core::ReceivedMessageDesc::ReceivePolicyDesc, receive_policy_type_name) );
				if(result < 0 ) return false;
				
				result = script_engine->RegisterObjectProperty(getRegisteredName(), "Core::Properties receive_policy_options", asOFFSET(Core::ReceivedMessageDesc::ReceivePolicyDesc, receive_policy_options) );
				if(result < 0 ) return false;
				
				return true;
			}
		};
	}
}