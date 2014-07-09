#pragma once

#include <string>
#include <vector>
#include <Properties/Properties.h>

namespace UnknownEngine{

	namespace Core{

		/**
		 * @brief %Message listener desctiptor
		 *
		 * This descriptor is used by a component factory to register needed listeners
		 *
		 * ###Concept
		 * This class was created simultaneously with scene loader class. The main purpose is to tell object factory
		 * which listeners need to be created for component/subsystem. A list of such descriptors is stored in a
		 * subsystem/listener descriptor and the factory must take care to create and register such listeners.
		 *
		 * ###Usage
		 * When a user code (e.g. a loader) wants to create a component it must say which messages this component will wait for.
		 * The engine doesn't know, how the component will receive messages (it may be the standalone subsystem's part
		 * e.g. OGRE entity and listen a message through proxy or be a listener itself). That's why we need to provide this data to
		 * factory somehow. We are saying which listeners we want to be created and how they need to be configured by providing
		 * such data in a subsystem/component descriptor. The subsystem itself must take care to create needed components.
		 * They are free to throw exceptions or just ignore unknown message listener types.
		 *
		 * ###Notes
		 *
		 *
		 */
		struct MessageListenerDesc
		{
			/**
			 * @brief Descriptor of single message subscription for listener
			 */
			struct MessageDesc
			{
				std::string message_type_name; ///< %String message type representation
				std::string receive_policy_type_name; ///< %Message receive policy name
				Properties receive_policy_options; ///< %Message receive policy options
			};

			std::string name; ///< %Message listener name
			std::vector<MessageDesc> messages; ///< %Message subscriptions list
		};

	}
}
