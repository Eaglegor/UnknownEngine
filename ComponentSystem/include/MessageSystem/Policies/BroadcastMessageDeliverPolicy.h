#pragma once

/*
 * BroadcastMessageDeliverPolicy.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: Eaglegor
 */
#include <ComponentSystem_export.h>
#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <MessageSystem/Policies/MessagePolicyType.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief \ref IMessageDeliveryPolicy "Delivery policy" allowing message delivery to all listeners
		 */
		class BroadcastMessageDeliverPolicy : public IMessageDeliveryPolicy
		{
			public:
				/**
				 * @brief Always returns true
				 * @param listener - Listener to check for
				 * @return true
				 */
				COMPONENTSYSTEM_EXPORT
				virtual bool allowDeliveryToListener(const IMessageListener* listener) const override;

				static const MessagePolicyType getType(){return "BroadcastMessageDeliverPolicy";}

				virtual ~BroadcastMessageDeliverPolicy (){}
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
