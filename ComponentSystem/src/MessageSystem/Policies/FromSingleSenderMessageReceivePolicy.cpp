/*
 * FromSingleSenderMessageReceivePolicy.cpp
 *
 *  Created on: 19 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <MessageSystem/Message.h>
#include <MessageSystem/Policies/FromSingleSenderMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		FromSingleSenderMessageReceivePolicy::FromSingleSenderMessageReceivePolicy ( std::string sender_name )
				: sender_name( sender_name )
		{
			// TODO Auto-generated constructor stub
		}

		bool FromSingleSenderMessageReceivePolicy::acceptMessage ( const Message& msg )
		{
			return msg.getSenderName() == sender_name;
		}

		FromSingleSenderMessageReceivePolicy::~FromSingleSenderMessageReceivePolicy ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
