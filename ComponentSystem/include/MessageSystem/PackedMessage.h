#pragma once
/*
 * Message.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>
#include <unordered_map>

#include <InlineSpecification.h>
#include <Properties/Properties.h>
#include <MessageSystem/MessageType.h>
#include <MessageSystem/MessageSystemParticipantId.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PackedMessage
		{
			public:
				PackedMessage ( const NumericIdentifierType &message_type_id, const MessageSystemParticipantId &sender_info )
						: message_type_id ( message_type_id ), sender_info ( sender_info )
				{
				}

				virtual ~PackedMessage ()
				{
				}

				UNKNOWNENGINE_INLINE
				virtual MessageType getMessageTypeId () const
				{
					return message_type_id;
				}

				UNKNOWNENGINE_INLINE
				MessageSystemParticipantId getSenderInfo () const
				{
					return sender_info;
				}

				UNKNOWNENGINE_INLINE
				Properties &getProperties ()
				{
					return properties;
				}

				UNKNOWNENGINE_INLINE
				const Properties &getProperties () const
				{
					return properties;
				}

			private:
				MessageType message_type_id;
				Properties properties;
				MessageSystemParticipantId sender_info;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
