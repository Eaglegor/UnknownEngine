#pragma once

#include <string>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>
#include <MessageSystem/Policies/MessagePolicyType.h>
#include <MessageSystem/MessageSystemParticipantId.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageSender;

		class FromSingleSenderMessageReceivePolicy: public IMessageReceivePolicy
		{
			public:
				FromSingleSenderMessageReceivePolicy(const MessageSystemParticipantId &sender_info);
				virtual ~FromSingleSenderMessageReceivePolicy();

				virtual bool allowReceiveFromSender ( IMessageSender* message_sender ) const override;

				virtual bool acceptMessage ( const PackedMessage &msg ) override;

				virtual MessageReceivePolicyType getType() const;
				
				constexpr static const char* getTypeName()
				{
					return "FromSingleSender";
				}

			private:
				MessageSystemParticipantId sender_info;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
