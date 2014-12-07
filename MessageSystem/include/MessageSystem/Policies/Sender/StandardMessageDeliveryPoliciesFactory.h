#pragma once

#include <MessageSystem/Policies/Sender/BaseMessageDeliveryPolicyFactory.h>

namespace UnknownEngine
{
	namespace Core
	{
		class StandardMessageDeliveryPoliciesFactory : public BaseMessageDeliveryPolicyFactory
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