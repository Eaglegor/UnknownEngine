#include <stdafx.h>

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/Policies/Sender/SingleReceiverMessageDeliverPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		SingleReceiverMessageDeliverPolicy::SingleReceiverMessageDeliverPolicy ( const std::string &receiver_name )
			: receiver_name ( receiver_name )
		{
			// TODO Auto-generated constructor stub

		}

		MessageDeliveryPolicyType SingleReceiverMessageDeliverPolicy::getType() const
		{
			return MESSAGE_DELIVERY_POLICY_TYPE_ID(getTypeName());
		}
		
		bool SingleReceiverMessageDeliverPolicy::allowDeliveryToListener ( const IMessageListener* listener ) const
		{
			return receiver_name == listener->getName();
		}

		SingleReceiverMessageDeliverPolicy::~SingleReceiverMessageDeliverPolicy ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
