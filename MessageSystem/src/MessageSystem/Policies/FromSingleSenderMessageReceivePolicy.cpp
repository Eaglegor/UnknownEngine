#include <stdafx.h>

#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/Policies/Listener/FromSingleSenderMessageReceivePolicy.h>
#include <MessageSystem/IMessageSender.h>

namespace UnknownEngine
{
	namespace Core
	{

		FromSingleSenderMessageReceivePolicy::FromSingleSenderMessageReceivePolicy ( const std::string &sender_info )
			: sender_info ( sender_info )
		{
			// TODO Auto-generated constructor stub
		}

		bool FromSingleSenderMessageReceivePolicy::allowReceiveFromSender ( IMessageSender* message_sender ) const
		{
			return sender_info == message_sender->getName();
		}
		
		bool FromSingleSenderMessageReceivePolicy::acceptMessage ( const PackedMessage& msg )
		{
			return true;
		}

		MessageReceivePolicyType FromSingleSenderMessageReceivePolicy::getType() const
		{
			return MESSAGE_RECEIVE_POLICY_TYPE_ID(getTypeName());
		}
		
		FromSingleSenderMessageReceivePolicy::~FromSingleSenderMessageReceivePolicy ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
