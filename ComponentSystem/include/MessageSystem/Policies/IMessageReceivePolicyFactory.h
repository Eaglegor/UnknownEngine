#pragma once

#include <MessageSystem/Policies/IMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IMessageReceivePolicyFactory
		{
		public:
			virtual IMessageReceivePolicy* create() = 0;
			virtual void destroy(IMessageReceivePolicy* policy) = 0;
		};
	}
}