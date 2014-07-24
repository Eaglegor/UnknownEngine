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
		 * It's assumed that each component/subsystem has **at most one** listener registered at the message bus
		 * and it's name is the same as the component's/subsystem's name.
		 *
		 * ###Usage
		 * When a user code (e.g. a loader) wants to create a component it must say which messages this component will wait for.
		 * The engine doesn't know, how the component will receive messages (it may be the standalone subsystem's part
		 * e.g. OGRE entity and listen a message through proxy or be a listener itself). That's why we need to provide this data to
		 * factory somehow. We are saying which messages we want to receive in the subsystem/component. Later the factory will
		 * create the listener accepting specified message types for a component/subsystem.
		 *
		 */

			/**
			 * @brief Descriptor of single message subscription for listener
			 */
			struct ReceivedMessageDesc
			{
				std::string message_type_name; ///< %String message type representation
				std::string receive_policy_type_name; ///< %Message receive policy name
				Properties receive_policy_options; ///< %Message receive policy options
			};

			typedef std::vector<ReceivedMessageDesc> ReceivedMessageDescriptorsList; ///< %Message subscriptions list

	}
}
