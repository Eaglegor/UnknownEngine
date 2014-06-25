#pragma once

#include <vector>
#include <Properties/Properties.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <Objects/Component.h>

namespace UnknownEngine
{
	namespace Core
	{
		class Entity;

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
