/*
 * IMessageListener.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <stdafx.h>

#include <MessageSystem/IMessageListener.h>

namespace UnknownEngine
{
	namespace Core
	{

		IMessageListener::IMessageListener (const std::string &object_name)
				: IMessageSystemParticipant(object_name)
		{
			// TODO Auto-generated constructor stub
		}

		IMessageListener::~IMessageListener ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
