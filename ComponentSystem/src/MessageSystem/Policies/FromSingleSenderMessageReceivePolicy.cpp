/*
 * FromSingleSenderMessageReceivePolicy.cpp
 *
 *  Created on: 19 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/Policies/FromSingleSenderMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		FromSingleSenderMessageReceivePolicy::FromSingleSenderMessageReceivePolicy ( SenderInfo sender_info )
				: sender_info( sender_info )
		{
			// TODO Auto-generated constructor stub
		}

		bool FromSingleSenderMessageReceivePolicy::acceptMessage ( const PackedMessage& msg )
		{
			return msg.getSenderInfo() == sender_info;
		}

		FromSingleSenderMessageReceivePolicy::~FromSingleSenderMessageReceivePolicy ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
