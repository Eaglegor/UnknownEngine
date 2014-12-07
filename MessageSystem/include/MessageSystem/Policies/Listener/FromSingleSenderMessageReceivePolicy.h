#pragma once

#include <string>
#include <MessageSystem/Policies/Listener/IMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageSender;

		class FromSingleSenderMessageReceivePolicy: public IMessageReceivePolicy
		{
			public:
				FromSingleSenderMessageReceivePolicy(const std::string &sender_name);
				virtual ~FromSingleSenderMessageReceivePolicy();

				virtual bool allowReceiveFromSender ( IMessageSender* message_sender ) const override;

				virtual bool acceptMessage ( const PackedMessage &msg ) override;

				virtual MessageReceivePolicyType getType() const;
				
				constexpr static const char* getTypeName()
				{
					return "FromSingleSender";
				}

			private:
				const std::string sender_info;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
