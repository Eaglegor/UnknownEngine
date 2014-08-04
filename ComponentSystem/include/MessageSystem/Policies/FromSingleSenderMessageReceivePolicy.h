#pragma once

/*
 * FromSingleSenderMessageReceivePolicy.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: Eaglegor
 */

#include <ComponentSystem_export.h>
#include <string>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>
#include <MessageSystem/Policies/MessagePolicyType.h>
#include <MessageSystem/MessageSystemParticipantId.h>

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
				COMPONENTSYSTEM_EXPORT
				virtual bool acceptMessage(const PackedMessage &msg) override;

				/**
				 * @brief Constructor
				 * @param sender_info - Message sender info to compare with
				 */
				COMPONENTSYSTEM_EXPORT
				FromSingleSenderMessageReceivePolicy (const MessageSystemParticipantId &sender_info);

				COMPONENTSYSTEM_EXPORT
				virtual ~FromSingleSenderMessageReceivePolicy ();

				static const MessagePolicyType getType(){return "FromSingleSenderMessageReceivePolicy";}

			private:
				MessageSystemParticipantId sender_info; ///< Message sender info to compare with
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
