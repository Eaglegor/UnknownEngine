#pragma once

#include <MessageSystem/Policies/Listener/BaseMessageReceivePolicyFactory.h>

namespace UnknownEngine
{
	namespace Core
	{
		class StandardMessageReceivePoliciesFactory : public BaseMessageReceivePolicyFactory
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