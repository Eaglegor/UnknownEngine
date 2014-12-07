#pragma once

#include <MessageSystem_export.h>
#include <MessageSystem/Policies/Listener/MessageReceivePolicyType.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageSender;

		class PackedMessage;

		class IMessageReceivePolicy
		{
			public:
				MESSAGESYSTEM_EXPORT
				virtual bool allowReceiveFromSender( IMessageSender* message_sender ) const = 0;

				MESSAGESYSTEM_EXPORT
				virtual MessageReceivePolicyType getType() const = 0;
				
				MESSAGESYSTEM_EXPORT
				virtual bool acceptMessage ( const PackedMessage &msg ) = 0;

				MESSAGESYSTEM_EXPORT
				virtual ~IMessageReceivePolicy()
				{
				}
		};

	} /* namespace Core */
	
	UNKNOWNENGINE_INLINE
	Core::MessageReceivePolicyType MESSAGE_RECEIVE_POLICY_TYPE_ID(const char* type_name)
	{
		return Core::MessageReceivePolicyType(type_name);
	}
	
} /* namespace UnknownEngine */
