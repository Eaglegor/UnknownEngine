#include <stdafx.h>

#include <MessageSystem/Policies/Sender/BroadcastMessageDeliverPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{
		bool BroadcastMessageDeliverPolicy::allowDeliveryToListener ( const IMessageListener* listener ) const
		{
			return true;
		}

		MessageDeliveryPolicyType BroadcastMessageDeliverPolicy::getType() const
		{
			return MESSAGE_DELIVERY_POLICY_TYPE_ID(getTypeName());
		}
		
	} /* namespace Core */
} /* namespace UnknownEngine */
