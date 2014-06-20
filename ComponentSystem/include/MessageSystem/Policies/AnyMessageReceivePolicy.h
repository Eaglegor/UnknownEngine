#pragma once

/*
 * AnyMessageReceivePolicy.h
 *
 *  Created on: 19 ���� 2014 �.
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

				virtual bool acceptMessage(const PackedMessage &msg);
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
