/*
 * SingleReceiverMessageDeliverPolicy.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/Policies/SingleReceiverMessageDeliverPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		SingleReceiverMessageDeliverPolicy::SingleReceiverMessageDeliverPolicy (const MessageSystemParticipantId &receiver_info)
				: receiver_info( receiver_info )
		{
			// TODO Auto-generated constructor stub

		}

		bool SingleReceiverMessageDeliverPolicy::allowDeliveryToListener ( const IMessageListener* listener ) const
		{
			return listener->getMessageSystemParticipantId() == receiver_info;
		}

		SingleReceiverMessageDeliverPolicy::~SingleReceiverMessageDeliverPolicy ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
