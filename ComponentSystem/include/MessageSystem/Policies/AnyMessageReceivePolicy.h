#pragma once

/*
 * AnyMessageReceivePolicy.h
 *
 *  Created on: 19 июня 2014 г.
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

				virtual bool acceptMessage(const PackedMessage &msg) override;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
