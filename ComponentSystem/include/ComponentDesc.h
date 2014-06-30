#pragma once

#include <vector>
#include <Properties/Properties.h>
#include <ComponentType.h>

namespace UnknownEngine
{
	namespace Core
	{
		class Entity;
		class MessageListenerDesc;

		struct ComponentDesc
		{
			Entity* entity;
			std::string name;
			ComponentType type;
			Properties creation_options;
			std::vector<MessageListenerDesc> message_listeners_desc;
		};
	}
}
