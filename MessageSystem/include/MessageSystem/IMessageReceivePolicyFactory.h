#pragma once

#include <AbstractObjectFactory.h>
#include <MessageSystem/MessageReceivePolicyType.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IMessageReceivePolicy;
		struct MessageReceivePolicyDesc;
		
		typedef AbstractObjectFactory<IMessageReceivePolicy, MessageReceivePolicyType, MessageReceivePolicyDesc> IMessageReceivePolicyFactory;
	}
}