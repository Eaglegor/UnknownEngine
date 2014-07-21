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

		/**
		 * @brief Descriptor of component to be passed to the component factory.
		 */
		struct ComponentDesc
		{
			std::string name; ///< Local name of component in the entity
			ComponentType type; ///< Type identifier of component
			Properties creation_options; ///< Options passed to the factory to create the component.
			std::vector<MessageListenerDesc> message_listeners_desc; ///< List of listeners to register from component factory
		};
	}
}
