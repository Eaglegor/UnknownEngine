#pragma once

/*
 * SingleReceiverMessageDeliverPolicy.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: Eaglegor
 */

#include <ComponentSystem_export.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <MessageSystem/Policies/MessagePolicyType.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief \ref IMessageDeliveryPolicy "Delivery policy" allowing only the specific listener to process a message
		 */
		class SingleReceiverMessageDeliverPolicy: public IMessageDeliveryPolicy
		{
			public:
				/**
				 * @brief Returns true if a listener's address equals the expected
				 * @param listener - Listener to check for
				 * @return true if a listener's address equals the expected
				 */
				COMPONENTSYSTEM_EXPORT
				virtual bool allowDeliveryToListener(const IMessageListener* listener) const override;

				/**
				 * @brief Constructor
				 * @param receiver_info - Listener address to compare with
				 */
				COMPONENTSYSTEM_EXPORT
				SingleReceiverMessageDeliverPolicy (const MessageSystemParticipantId &receiver_info);

				COMPONENTSYSTEM_EXPORT
				virtual ~SingleReceiverMessageDeliverPolicy ();

				static const MessagePolicyType getType(){return "SingleReceiverMessageDeliverPolicy";}

			private:
				MessageSystemParticipantId receiver_info; ///< Listener address to compare with
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
