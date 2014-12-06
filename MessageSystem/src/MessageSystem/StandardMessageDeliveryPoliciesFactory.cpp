#include <MessageSystem/StandardMessageDeliveryPoliciesFactory.h>
#include <MessageSystem/Policies/BroadcastMessageDeliverPolicy.h>
#include <MessageSystem/Policies/SingleReceiverMessageDeliverPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{
		StandardMessageDeliveryPoliciesFactory::StandardMessageDeliveryPoliciesFactory()
		{
			CreatableObjectDesc desc;
			desc.type = MESSAGE_DELIVERY_POLICY_TYPE_ID(BroadcastMessageDeliverPolicy::getTypeName());
			desc.creator = std::bind(&StandardMessageDeliveryPoliciesFactory::createBroadcastMessageDeliveryPolicy, this, std::placeholders::_1);
			registerCreator(desc);
			
			desc.type = MESSAGE_DELIVERY_POLICY_TYPE_ID(SingleReceiverMessageDeliverPolicy::getTypeName());
			desc.creator = std::bind(&StandardMessageDeliveryPoliciesFactory::createSingleReceiverReceivePolicy, this, std::placeholders::_1);
			registerCreator(desc);
		}
		
		const char* StandardMessageDeliveryPoliciesFactory::getName() const
		{
			return "Core.StandardMessageDeliveryPoliciesFactory";
		}
		
		IMessageDeliveryPolicy* StandardMessageDeliveryPoliciesFactory::createBroadcastMessageDeliveryPolicy ( const MessageDeliveryPolicyDesc& desc )
		{
			return new BroadcastMessageDeliverPolicy();
		}

		IMessageDeliveryPolicy* StandardMessageDeliveryPoliciesFactory::createSingleReceiverReceivePolicy ( const MessageDeliveryPolicyDesc& desc )
		{
			MessageSystemParticipantId receiver_id ( desc.options.get<std::string> ( "receiver_name" ) );
			return new SingleReceiverMessageDeliverPolicy ( receiver_id );
		}

	}
}