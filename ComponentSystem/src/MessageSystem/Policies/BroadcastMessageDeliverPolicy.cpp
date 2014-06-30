/*
 * BroadcastMessageDeliverPolicy.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <MessageSystem/Policies/BroadcastMessageDeliverPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		BroadcastMessageDeliverPolicy::BroadcastMessageDeliverPolicy ()
		{
			// TODO Auto-generated constructor stub

		}

		bool BroadcastMessageDeliverPolicy::allowDeliveryToListener ( const IMessageListener* listener ) const
		{
			return true;
		}

		BroadcastMessageDeliverPolicy::~BroadcastMessageDeliverPolicy ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
