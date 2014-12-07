#pragma once

#include <MessageSystem/Policies/Listener/IMessageReceivePolicy.h>
#include <MessageSystem/Policies/Listener/MessageReceivePolicyType.h>

namespace UnknownEngine
{
	namespace Core
	{

		class AnyMessageReceivePolicy : public IMessageReceivePolicy
		{
			public:
				virtual bool allowReceiveFromSender ( IMessageSender* message_sender ) const override;
				
				virtual bool acceptMessage ( const PackedMessage &msg ) override;

				virtual MessageReceivePolicyType getType() const;
				
				constexpr static const char* getTypeName()
				{
					return "Any";
				}

				virtual ~AnyMessageReceivePolicy () {}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
