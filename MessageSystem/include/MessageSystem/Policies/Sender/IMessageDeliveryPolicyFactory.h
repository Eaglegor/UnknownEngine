#pragma once

#include <MessageSystem_export.h>
#include <MessageSystem/Policies/Sender/MessageDeliveryPolicyType.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct MessageDeliveryPolicyDesc;
		class IMessageDeliveryPolicy;
		
		class IMessageDeliveryPolicyFactory
		{
			public:
				MESSAGESYSTEM_EXPORT
				virtual ~IMessageDeliveryPolicyFactory(){}

				MESSAGESYSTEM_EXPORT
				virtual const char* getName() const = 0;

				MESSAGESYSTEM_EXPORT
				virtual bool supportsType ( const MessageDeliveryPolicyType &object_type ) const = 0;

				MESSAGESYSTEM_EXPORT
				virtual IMessageDeliveryPolicy* createObject ( const MessageDeliveryPolicyDesc& desc ) = 0;

				MESSAGESYSTEM_EXPORT
				virtual void destroyObject ( IMessageDeliveryPolicy* object ) = 0;
		};

	} // namespace Core
} // namespace UnknownEngine
