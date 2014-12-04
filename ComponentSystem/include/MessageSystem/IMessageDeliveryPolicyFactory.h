#pragma once

#include <AbstractObjectFactory.h>
#include <MessageSystem/MessageDeliveryPolicyType.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IMessageDeliveryPolicy;
		struct MessageDeliveryPolicyDesc;
		
		typedef AbstractObjectFactory<IMessageDeliveryPolicy, MessageDeliveryPolicyType, MessageDeliveryPolicyDesc> IMessageDeliveryPolicyFactory;
	}
}