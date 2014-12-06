#pragma once

#include <MessageSystem/MessageSystemParticipantId.h>
#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <MessageSystem/Policies/MessagePolicyType.h>

namespace UnknownEngine
{
	namespace Core
	{

		class SingleReceiverMessageDeliverPolicy: public IMessageDeliveryPolicy
		{
			public:

				virtual bool allowDeliveryToListener ( const IMessageListener* listener ) const override;

				SingleReceiverMessageDeliverPolicy ( const MessageSystemParticipantId &receiver_info );

				virtual ~SingleReceiverMessageDeliverPolicy ();

				virtual MessageDeliveryPolicyType getType() const;
				
				constexpr static const char* getTypeName()
				{
					return "SingleReceiver";
				}

			private:
				MessageSystemParticipantId receiver_info;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
