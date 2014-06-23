/*
 * AnyMessageReceivePolicy.cpp
 *
 *  Created on: 19 июня 2014 г.
 *      Author: Eaglegor
 */

#include <MessageSystem/Policies/AnyMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		AnyMessageReceivePolicy::AnyMessageReceivePolicy ()
		{
			// TODO Auto-generated constructor stub

		}

		AnyMessageReceivePolicy::~AnyMessageReceivePolicy ()
		{
			// TODO Auto-generated destructor stub
		}

		bool AnyMessageReceivePolicy::acceptMessage ( const PackedMessage& msg )
		{
			return true;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
