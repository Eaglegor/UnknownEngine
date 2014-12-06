#pragma once

#include <MessageSystem/BaseMessageDeliveryPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{
		class StandardMessageDeliveryPoliciesFactory : public BaseMessageDeliveryPolicy
		{
		public:
			StandardMessageDeliveryPoliciesFactory();
			virtual const char* getName() const;
			
		private:
			IMessageDeliveryPolicy* createBroadcastMessageDeliveryPolicy(const MessageDeliveryPolicyDesc &desc);
			IMessageDeliveryPolicy* createSingleReceiverReceivePolicy(const MessageDeliveryPolicyDesc &desc);
			
		};
	}
}