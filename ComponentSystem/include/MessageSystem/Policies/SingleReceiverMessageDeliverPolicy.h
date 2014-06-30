#pragma once

/*
 * SingleReceiverMessageDeliverPolicy.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: Eaglegor
 */

#include <MessageSystem/MessageSystemParticipantId.h>
#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		class SingleReceiverMessageDeliverPolicy: public IMessageDeliveryPolicy
		{
			public:
				virtual bool allowDeliveryToListener(const IMessageListener* listener) const override;

				SingleReceiverMessageDeliverPolicy (const MessageSystemParticipantId &receiver_info);
				virtual ~SingleReceiverMessageDeliverPolicy ();

			private:
				MessageSystemParticipantId receiver_info;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
