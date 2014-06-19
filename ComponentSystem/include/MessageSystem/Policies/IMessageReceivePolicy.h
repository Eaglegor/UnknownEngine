#pragma once

/*
 * IMessageReceivePolicy.h
 *
 *  Created on: 19 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageReceivePolicy
		{
			public:
				virtual bool acceptMessage(const Message &msg) = 0;
				virtual ~IMessageReceivePolicy ();

			protected:
				IMessageReceivePolicy ();
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
