/*
 * IMessageListener.cpp
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <MessageSystem/IMessageListener.h>

namespace UnknownEngine
{
	namespace Core
	{

		IMessageListener::IMessageListener ()
				: message_receive_policy( nullptr )
		{
			// TODO Auto-generated constructor stub

		}

		IMessageListener::~IMessageListener ()
		{
			// TODO Auto-generated destructor stub
		}

		IMessageReceivePolicy* IMessageListener::getMessageReceivePolicy () const
		{
			return message_receive_policy;
		}

		void IMessageListener::setMessageReceivePolicy ( IMessageReceivePolicy* policy )
		{
			message_receive_policy = policy;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
