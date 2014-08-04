#pragma once
/*
 * Message.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <ComponentSystem_export.h>
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

		/**
		 * @brief Generic message class to be sent over a message bus
		 *
		 *	###Concept
		 *	Packed message is a generic message representation. It is defined by:
		 *  - \ref MessageType "type". Used to dispatch message to listeners.
		 *  - \ref Properties "properties" with std::string keys. Holds actual data.
		 *  - \ref MessageSystemParticipantId "information about sender". Can be used in different ways (e.g. filter out messages)
		 *
		 *	###Usage
		 *	When user code wants to pass some command/information to some component/subsystem,
		 *  it creates a packed message, fills it's properties and passes it to a MessageDispatcher::deliverMessage() method.
		 *  User code must specify a sender info. One way to do this is to inherit class which wants to send message from
		 *  IMessageSystemParticipant base class and then pass the info returned by
		 *	IMessageSystemParticipant::getMessageSystemParticipantId() to the message.
		 *
		 *	###Notes
		 *
		 * 	**It's not recommended to compose a packed message manually (although you still can).**
		 *  The better way is to use a concept of \ref MessagePacker "message packer"/ \ref MessageUnpacker "message unpacker"
		 *	which can convert a concrete message class to a	packed message and vice versa.
		 *	Message packers and unpackers can check message's format and notify user that something is wrong
		 *  (e.g. mandatory parameters are not set or there is an incorrect value).
		 *	Packers and unpackers are recommended to be exposed in header files of subsystem along with a concrete message
		 *	types defined in subsystem.
		 *
		 *	Packing message as properties map could be replaced with something more performance-friendly later.
		 *  So if you've decided to compose packed message manually you must remember that if the format of packing
		 *  will change, you will need to **rewrite all parts of code where you've sent messages***. Using a concept
		 *  of packer/unpacker you will just need to rewrite packers/unpackers which is much easier to do.
		 *
		 */
		class PackedMessage
		{
			public:
				/**
				 * @brief Constructor
				 * @param message_type_id - numeric identifier of message type (can be obtained by call to MessageDictionary)
				 * @param sender_info - information about message sender
				 */
				PackedMessage ( const NumericIdentifierType &message_type_id, const MessageSystemParticipantId &sender_info )
					: message_type_id ( message_type_id ), sender_info ( sender_info )
				{
				}

				virtual ~PackedMessage ()
				{
				}

				/**
				 *
				 * @brief Returns numeric message type identifier
				 * @return Numeric message type identifier.
				 *
				 */
				UNKNOWNENGINE_INLINE
				virtual MessageType getMessageTypeId () const
				{
					return message_type_id;
				}

				/**
				 *
				 * @brief Returns information about message sender
				 * @return Information about message sender
				 *
				 */
				UNKNOWNENGINE_INLINE
				MessageSystemParticipantId getSenderInfo () const
				{
					return sender_info;
				}

				/**
				 *
				 * @brief Returns non-const map of properties avaiable to edit
				 * @return Non-const properties map
				 *
				 */
				UNKNOWNENGINE_INLINE
				Properties &getProperties ()
				{
					return properties;
				}

				/**
				 *
				 * @brief Returns const read-only map of properties
				 * @return Read-only map of properties
				 *
				 */
				UNKNOWNENGINE_INLINE
				const Properties &getProperties () const
				{
					return properties;
				}

			private:
				MessageType message_type_id; ///< Numeric message type identifier
				Properties properties; ///< Properties map
				MessageSystemParticipantId sender_info; ///< Information about sender

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
