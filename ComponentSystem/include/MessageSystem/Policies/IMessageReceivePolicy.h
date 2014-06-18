#pragma once

/*
 * IMessageReceivePolicy.h
 *
 *  Created on: 19 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

namespace UnknownEngine
{
	namespace Core
	{

		class Message;

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
