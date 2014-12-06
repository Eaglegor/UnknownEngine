#pragma once

#include <MessageSystem/MessageDeliveryPolicyType.h>
#include <Properties/Properties.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct MessageDeliveryPolicyDesc
		{
			MessageDeliveryPolicyType type;
			Properties options;
		};
	}
}