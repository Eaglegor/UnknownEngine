#pragma once

/*
 * SingleReceiverMessageDeliverPolicy.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: Eaglegor
 */

#include <string>
#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		class SingleReceiverMessageDeliverPolicy: public IMessageDeliveryPolicy
		{
			public:

				virtual bool allowDeliverToListener(const IMessageListener* listener) const override;

				SingleReceiverMessageDeliverPolicy (std::string receiver_name);
				virtual ~SingleReceiverMessageDeliverPolicy ();

			private:
				std::string receiver_name;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
