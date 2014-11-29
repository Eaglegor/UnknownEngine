#pragma once

#include <MessageSystem/MessageListenerDesc.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class ReceivedMessageDescWrapper
		{
		public:
			static void set_receive_policy(Core::ReceivedMessageDesc* this_ptr, const Core::ReceivedMessageDesc::ReceivePolicyDesc& value)
			{
				this_ptr->receive_policy = value;
			}
		};
	}
}