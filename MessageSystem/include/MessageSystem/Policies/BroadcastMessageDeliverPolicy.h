#pragma once

#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <MessageSystem/Policies/MessagePolicyType.h>

namespace UnknownEngine
{
	namespace Core
	{

		class BroadcastMessageDeliverPolicy : public IMessageDeliveryPolicy
		{
			public:
				virtual bool allowDeliveryToListener ( const IMessageListener* listener ) const override;

				virtual MessageDeliveryPolicyType getType() const;
				
				constexpr static const char* getTypeName()
				{
					return "Broadcast";
				}

				virtual ~BroadcastMessageDeliverPolicy () {}
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
