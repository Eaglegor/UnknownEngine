#include <stdafx.h>

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/Policies/SingleReceiverMessageDeliverPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		SingleReceiverMessageDeliverPolicy::SingleReceiverMessageDeliverPolicy ( const MessageSystemParticipantId &receiver_info )
			: receiver_info ( receiver_info )
		{
			// TODO Auto-generated constructor stub

		}

		MessageDeliveryPolicyType SingleReceiverMessageDeliverPolicy::getType() const
		{
			return MESSAGE_DELIVERY_POLICY_TYPE_ID(getTypeName());
		}
		
		bool SingleReceiverMessageDeliverPolicy::allowDeliveryToListener ( const IMessageListener* listener ) const
		{
			return listener->getMessageSystemParticipantId() == receiver_info;
		}

		SingleReceiverMessageDeliverPolicy::~SingleReceiverMessageDeliverPolicy ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
