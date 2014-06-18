/*
 * AnyMessageReceivePolicy.cpp
 *
 *  Created on: 19 θώνÿ 2014 γ.
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

		bool AnyMessageReceivePolicy::acceptMessage ( const Message& msg )
		{
			return true;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
