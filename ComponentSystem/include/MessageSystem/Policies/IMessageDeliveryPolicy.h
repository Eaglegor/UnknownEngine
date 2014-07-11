#pragma once

/*
 * IMessageDeliveryPolicy.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: Eaglegor
 */

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageListener;

		/**
		 * @brief Class to filter out messages for the listener
		 *
		 * ###Concept
		 * The first line of filtering is the message type. The listener doesn't receive messages of specific type
		 * if it wasn't registered to receive them. The second line is the delivery policy of sent message. Listener doesn't receive
		 * message if the delivery policy says so (e.g. because it's address). The third line of filtering is a receive policy of listener.
		 *
		 * If delivery policy says that the message must not be passed to a listener, it will not be passed to it.
		 *
		 * ###Usage
		 * When you send a message you can pass a delivery policy along. It may be a predefined policy (broadcast, specific receiver) or
		 * your own policy inherited from IMessageDeliveryPolicy. When you define your own policy you must implement the
		 * allowDeliveryToListener() method. Optionally you may also override notifySuccessulyDelivered() and notifyDeliveryFinished() methods
		 * which are empty by default to define some behavior based on successful/unsuccessful delivery (e.g. deliver to the first accepted listener).
		 *
		 */

		class IMessageDeliveryPolicy
		{
			public:

				/**
				 * @brief Determines if the message must be passed to the specified listener
				 * @param listener - Listener to check for
				 * @return true if message must be passed to the listener
				 */
				virtual bool allowDeliveryToListener(const IMessageListener* listener) const = 0;

				/**
				 * @brief Callback to notify that the message was processed by a listener
				 *
				 * May be used in multithreaded subsystems to wait for message delivery.
				 *
				 */
				virtual void notifySuccessulyDelivered(){}

				/**
				 * @brief Callback to notify that message delivery was finished.
				 *
				 * Is called independently of delivery success when all listeners are checked to process message
				 *
				 */
				virtual void notifyDeliveryFinished(){}

				virtual ~IMessageDeliveryPolicy()
				{
				}
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
