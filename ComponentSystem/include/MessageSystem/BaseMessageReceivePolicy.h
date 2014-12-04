#pragma once

#include <MessageSystem/IMessageReceivePolicyFactory.h>
#include <BaseObjectFactory.h>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>
#include <MessageSystem/MessageReceivePolicyType.h>
#include <MessageSystem/MessageReceivePolicyDesc.h>

namespace UnknownEngine
{
	namespace Core
	{
		typedef BaseObjectFactory<IMessageReceivePolicy, MessageReceivePolicyType, MessageReceivePolicyDesc> BaseMessageReceivePolicy;
	}
}