#pragma once

#include <Properties/Properties.h>
#include <MessageSystem/Policies/MessagePolicyType.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct MessagingPolicyDesc
		{
			MessagePolicyType type;
			Properties creation_options;
		};
	}
}
