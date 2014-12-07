#pragma once

#include <MessageSystem/Policies/Listener/MessageReceivePolicyType.h>
#include <Properties/Properties.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct MessageReceivePolicyDesc
		{
			MessageReceivePolicyType type;
			Properties options;
		};
	}
}