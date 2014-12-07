#pragma once
#include <MessageSystem/Policies/Sender/IMessageDeliveryPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		class SingleReceiverMessageDeliverPolicy: public IMessageDeliveryPolicy
		{
			public:

				virtual bool allowDeliveryToListener ( const IMessageListener* listener ) const override;

				SingleReceiverMessageDeliverPolicy ( const std::string &receiver_name );

				virtual ~SingleReceiverMessageDeliverPolicy ();

				virtual MessageDeliveryPolicyType getType() const;
				
				constexpr static const char* getTypeName()
				{
					return "SingleReceiver";
				}

			private:
				std::string receiver_name;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
