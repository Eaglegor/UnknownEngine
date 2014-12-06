#pragma once

/*
 * IMessageDeliveryPolicy.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: Eaglegor
 */

#include <MessageSystem_export.h>
#include <MessageSystem/MessageDeliveryPolicyType.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageListener;

		class IMessageDeliveryPolicy
		{
			public:

				/**
				 * @brief Determines if the message must be passed to the specified listener
				 * @param listener - Listener to check for
				 * @return true if message must be passed to the listener
				 */
				MESSAGESYSTEM_EXPORT
				virtual bool allowDeliveryToListener ( const IMessageListener* listener ) const = 0;

				MESSAGESYSTEM_EXPORT
				virtual MessageDeliveryPolicyType getType() const = 0;
				
				MESSAGESYSTEM_EXPORT
				virtual ~IMessageDeliveryPolicy()
				{
				}
		};

	} /* namespace Core */
	
	UNKNOWNENGINE_INLINE
	Core::MessageDeliveryPolicyType MESSAGE_DELIVERY_POLICY_TYPE_ID(const char* type_name)
	{
		return Core::MessageDeliveryPolicyType(type_name);
	}
	
} /* namespace UnknownEngine */
