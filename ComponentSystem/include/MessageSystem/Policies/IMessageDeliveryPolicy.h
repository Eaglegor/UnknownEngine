#pragma once

/*
 * IMessageDeliveryPolicy.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageListener;

		class IMessageDeliveryPolicy
		{
			public:

				virtual bool allowDeliverToListener(const IMessageListener* listener) const = 0;
				virtual ~IMessageDeliveryPolicy ();

			protected:
				IMessageDeliveryPolicy ();
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
