#pragma once

#include <MessageSystem/MessageReceivePolicyType.h>
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