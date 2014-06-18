#pragma once

/*
 * FromSingleSenderMessageReceivePolicy.h
 *
 *  Created on: 19 θώνÿ 2014 γ.
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

				virtual bool acceptMessage(const Message &msg);

				FromSingleSenderMessageReceivePolicy (std::string sender_name);
				virtual ~FromSingleSenderMessageReceivePolicy ();

			private:
				std::string sender_name;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
