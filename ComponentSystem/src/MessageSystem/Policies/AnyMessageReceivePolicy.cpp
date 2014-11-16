/*
 * AnyMessageReceivePolicy.cpp
 *
 *  Created on: 19 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <MessageSystem/Policies/AnyMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{
		bool AnyMessageReceivePolicy::allowReceiveFromSender ( IMessageSender* message_sender )
		{
			return true;
		}
		
		bool AnyMessageReceivePolicy::acceptMessage ( const PackedMessage& msg )
		{
			return true;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
