#pragma once

/*
 * IMessageReceivePolicy.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: Eaglegor
 */

#include <ComponentSystem_export.h>
#include <MessageSystem/MessageReceivePolicyType.h>
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

				virtual bool allowReceiveFromSender( IMessageSender* message_sender ) const = 0;

				virtual MessageReceivePolicyType getType() const = 0;
				
				virtual bool acceptMessage ( const PackedMessage &msg ) = 0;

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
