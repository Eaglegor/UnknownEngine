#pragma once

#include <MessageSystem/BaseMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{
		class StandardMessageReceivePoliciesFactory : public BaseMessageReceivePolicy
		{
		public:
			StandardMessageReceivePoliciesFactory();
			virtual const char* getName() const;
			
		private:
			IMessageReceivePolicy* createAnyMessageReceivePolicy(const MessageReceivePolicyDesc &desc);
			IMessageReceivePolicy* createFromSingleSenderReceivePolicy(const MessageReceivePolicyDesc &desc);
			
		};
	}
}