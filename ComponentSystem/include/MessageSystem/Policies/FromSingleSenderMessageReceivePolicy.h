#pragma once

/*
 * FromSingleSenderMessageReceivePolicy.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: Eaglegor
 */

#include <string>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief \ref IMessageReceivePolicy "Receive policy" allowing only messages from specific sender to be processed
		 */
		class FromSingleSenderMessageReceivePolicy: public IMessageReceivePolicy
		{
			public:
				/**
				 * @brief Returns true if message sender is equal to expected
				 * @param msg - Message to analyze
				 * @return true if message sender is equal to expected
				 */
				virtual bool acceptMessage(const PackedMessage &msg) override;

				/**
				 * @brief Constructor
				 * @param sender_info - Message sender info to compare with
				 */
				FromSingleSenderMessageReceivePolicy (MessageSystemParticipantId sender_info);
				virtual ~FromSingleSenderMessageReceivePolicy ();

			private:
				MessageSystemParticipantId sender_info; ///< Message sender info to compare with
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
