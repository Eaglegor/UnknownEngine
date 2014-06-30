#pragma once

/*
 * IMessageDeliveryPolicy.h
 *
 *  Created on: 18 июня 2014 г.
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

				virtual bool allowDeliveryToListener(const IMessageListener* listener) const = 0;
				virtual void notifyDelivered(){}
				virtual ~IMessageDeliveryPolicy()
				{
				}

			protected:
				IMessageDeliveryPolicy()
				{
				}
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
