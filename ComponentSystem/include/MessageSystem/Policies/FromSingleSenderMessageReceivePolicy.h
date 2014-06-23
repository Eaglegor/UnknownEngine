#pragma once

/*
 * FromSingleSenderMessageReceivePolicy.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: Eaglegor
 */

#include <string>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		class FromSingleSenderMessageReceivePolicy: public IMessageReceivePolicy
		{
			public:

				virtual bool acceptMessage(const PackedMessage &msg);

				FromSingleSenderMessageReceivePolicy (SenderInfo sender_info);
				virtual ~FromSingleSenderMessageReceivePolicy ();

			private:
				SenderInfo sender_info;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
