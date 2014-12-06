/*
 * FromSingleSenderMessageReceivePolicy.cpp
 *
 *  Created on: 19 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/Policies/FromSingleSenderMessageReceivePolicy.h>
#include <MessageSystem/IMessageSender.h>

namespace UnknownEngine
{
	namespace Core
	{

		FromSingleSenderMessageReceivePolicy::FromSingleSenderMessageReceivePolicy ( const MessageSystemParticipantId &sender_info )
			: sender_info ( sender_info )
		{
			// TODO Auto-generated constructor stub
		}

		bool FromSingleSenderMessageReceivePolicy::allowReceiveFromSender ( IMessageSender* message_sender ) const
		{
			return message_sender->getMessageSystemParticipantId() == sender_info;
		}
		
		bool FromSingleSenderMessageReceivePolicy::acceptMessage ( const PackedMessage& msg )
		{
			return true;
		}

		MessageReceivePolicyType FromSingleSenderMessageReceivePolicy::getType() const
		{
			return MESSAGE_RECEIVE_POLICY_TYPE_ID(getTypeName());
		}
		
		FromSingleSenderMessageReceivePolicy::~FromSingleSenderMessageReceivePolicy ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
