#pragma once

#include <MessageSystem/IMessageDeliveryPolicyFactory.h>
#include <BaseObjectFactory.h>
#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <MessageSystem/MessageDeliveryPolicyType.h>
#include <MessageSystem/MessageDeliveryPolicyDesc.h>

namespace UnknownEngine
{
	namespace Core
	{
		typedef BaseObjectFactory<IMessageDeliveryPolicy, MessageDeliveryPolicyType, MessageDeliveryPolicyDesc> BaseMessageDeliveryPolicy;
	}
}