#include <MessageSystem/Policies/Listener/StandardMessageReceivePoliciesFactory.h>
#include <MessageSystem/Policies/Listener/AnyMessageReceivePolicy.h>
#include <MessageSystem/Policies/Listener/FromSingleSenderMessageReceivePolicy.h>
#include <MessageSystem/Policies/Listener/MessageReceivePolicyDesc.h>

namespace UnknownEngine
{
	namespace Core
	{
		StandardMessageReceivePoliciesFactory::StandardMessageReceivePoliciesFactory()
		{
			CreatableObjectDesc desc;
			desc.type = MESSAGE_RECEIVE_POLICY_TYPE_ID(AnyMessageReceivePolicy::getTypeName());
			desc.creator = std::bind(&StandardMessageReceivePoliciesFactory::createAnyMessageReceivePolicy, this, std::placeholders::_1);
			registerCreator(desc);
			
			desc.type = MESSAGE_RECEIVE_POLICY_TYPE_ID(FromSingleSenderMessageReceivePolicy::getTypeName());
			desc.creator = std::bind(&StandardMessageReceivePoliciesFactory::createFromSingleSenderReceivePolicy, this, std::placeholders::_1);
			registerCreator(desc);
		}
		
		const char* StandardMessageReceivePoliciesFactory::getName() const
		{
			return "Core.StandardMessageReceivePoliciesFactory";
		}
		
		IMessageReceivePolicy* StandardMessageReceivePoliciesFactory::createAnyMessageReceivePolicy ( const MessageReceivePolicyDesc& desc )
		{
			return new AnyMessageReceivePolicy();
		}

		IMessageReceivePolicy* StandardMessageReceivePoliciesFactory::createFromSingleSenderReceivePolicy ( const MessageReceivePolicyDesc& desc )
		{
			return new FromSingleSenderMessageReceivePolicy ( desc.options.get<std::string> ( "sender_name" ) );
		}
		
	}
}