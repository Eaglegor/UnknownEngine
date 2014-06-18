/*
 * SingleReceiverMessageDeliverPolicy.cpp
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/Policies/SingleReceiverMessageDeliverPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		SingleReceiverMessageDeliverPolicy::SingleReceiverMessageDeliverPolicy (std::string receiver_name)
				: receiver_name( receiver_name )
		{
			// TODO Auto-generated constructor stub

		}

		bool SingleReceiverMessageDeliverPolicy::allowDeliverToListener ( const IMessageListener* listener ) const
		{
			return listener->getName() == receiver_name;
		}

		SingleReceiverMessageDeliverPolicy::~SingleReceiverMessageDeliverPolicy ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
