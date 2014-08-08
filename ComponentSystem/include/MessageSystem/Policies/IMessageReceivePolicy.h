#pragma once

/*
 * IMessageReceivePolicy.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: Eaglegor
 */

#include <ComponentSystem_export.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PackedMessage;

		/**
		 * @brief Class to filter out messages for the listener
		 *
		 * ###Concept
		 * The first line of filtering is the message type. The listener doesn't receive messages of specific type
		 * if it wasn't registered to receive them. The second line is the delivery policy of sent message. Listener doesn't receive
		 * message if the delivery policy says so (e.g. because it's address). The third line of filtering is a receive policy of listener.
		 *
		 * If receive policy says that the message must not be processed, it will not be passed to a listener.
		 *
		 * ###Usage
		 * When you register a listener you pass a receive policy along. It may be one of inbuild policies (receive all, receive from sender, etc.) or
		 * you own policy. To define your own policy you must inherit from IMessageReceivePolicy and implement acceptMessage() method.
		 * If acceptMessage() returns false - the message won't be procesed by this listener.
		 *
		 */

		class IMessageReceivePolicy
		{
			public:

				/**
				 * @brief Determines if the message must be processed by a listener
				 * @param msg - Message to analyze
				 * @return true if the message must be processed
				 */
				virtual bool acceptMessage ( const PackedMessage &msg ) = 0;

				virtual ~IMessageReceivePolicy()
				{
				}
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
