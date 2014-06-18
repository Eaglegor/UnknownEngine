#pragma once

/*
 * AnyMessageReceivePolicy.h
 *
 *  Created on: 19 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <MessageSystem/Policies/IMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		class AnyMessageReceivePolicy : public IMessageReceivePolicy
		{
			public:
				AnyMessageReceivePolicy ();
				virtual ~AnyMessageReceivePolicy ();

				virtual bool acceptMessage(const Message &msg);
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
