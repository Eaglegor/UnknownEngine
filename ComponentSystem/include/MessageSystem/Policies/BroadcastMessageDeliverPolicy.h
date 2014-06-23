#pragma once

/*
 * BroadcastMessageDeliverPolicy.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: Eaglegor
 */
#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		class BroadcastMessageDeliverPolicy : public IMessageDeliveryPolicy
		{
			public:

				virtual bool allowDeliverToListener(const IMessageListener* listener) const override;

				BroadcastMessageDeliverPolicy ();
				virtual ~BroadcastMessageDeliverPolicy ();
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
