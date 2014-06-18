/*
 * BroadcastMessageDeliverPolicy.cpp
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <MessageSystem/Policies/BroadcastMessageDeliverPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		BroadcastMessageDeliverPolicy::BroadcastMessageDeliverPolicy ()
		{
			// TODO Auto-generated constructor stub

		}

		bool BroadcastMessageDeliverPolicy::allowDeliverToListener ( const IMessageListener* listener ) const
		{
			return true;
		}

		BroadcastMessageDeliverPolicy::~BroadcastMessageDeliverPolicy ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
