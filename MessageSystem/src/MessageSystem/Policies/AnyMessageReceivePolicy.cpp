#include <stdafx.h>

#include <MessageSystem/Policies/Listener/AnyMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{
		bool AnyMessageReceivePolicy::allowReceiveFromSender ( IMessageSender* message_sender ) const
		{
			return true;
		}

		MessageReceivePolicyType AnyMessageReceivePolicy::getType() const
		{
			return MESSAGE_RECEIVE_POLICY_TYPE_ID(getTypeName());
		}
		
		bool AnyMessageReceivePolicy::acceptMessage ( const PackedMessage& msg )
		{
			return true;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
