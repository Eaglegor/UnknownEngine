#pragma once

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
