#pragma once

#include <MessageSystem/Policies/Sender/IMessageDeliveryPolicy.h>

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
