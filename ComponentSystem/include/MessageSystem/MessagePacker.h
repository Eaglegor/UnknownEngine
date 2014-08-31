#pragma once
/*
 * MessageParser.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: gorbachenko
 */

#include <ComponentSystem_export.h>
#include <string>

#include <Exception.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <MessageSystem/MessageType.h>
#include <MessageSystem/InvalidMessageFormatException.h>

namespace UnknownEngine
{
	namespace Core
	{
		class PackedMessage;

		/**
		 * @brief Class to convert from concrete message class to a packed message
		 *
		 * \tparam T Concrete message class
		 *
		 * ###Concept
		 * Message dispatcher works with generic packed message containing some data having no compile time defined
		 * value types and names. Because we can't guarantee the correctness of manual packed message composing
		 * (there may be mistypes, incorrect values, copy-paste errors, missing mandatory fields etc.) we recommend
		 * to expose not just a message type but a concrete message class with 2 helper classes - message packer and
		 * message unpacker.
		 * The purpose of message packer is to convert a concrete message class (e.g. LogMessage) to the packed message
		 * using the appropriate format. The pair of message packer - the message unpacker - will then perform the vice versa
		 * conversion checking the message format.
		 *
		 * ###Usage
		 * The user code works with compile-time checked message classes exposed in header files of subsystem.
		 * The message packer and message unpacker need to be provided by a subsystem when declaring a message.
		 * When the user code wants to send message it creates a message class instance (e.g. LogMessage). Then it passes it to
		 * the message packer's packMessage() method and gets a PackedMessage in the appropriate format. After that this
		 * message can be sent with message dispatcher. When a listener receives the message it calls a message unpacker's method
		 * unpackMessage() and gets back a concrete message class, which fields name and type is checked at compile-time.
		 * The rule is: **Don't try to compose packed messages manually: use packer/unpacker model**. This rule is useful
		 * due to the fact that sometimes we may change the format of packed message for performance boost. If we use
		 * packer/unpacker model we just rewrite some isolated converter classes and don't touch logic part of code.
		 *
		 * ###Notes
		 * There is no magic. The user code still must know which message class it's converting and use an appropriate
		 * packer.
		 *
		 */
		template <typename T>
		class MessagePacker
		{
			public:
				/**
				 * @brief Construcror
				 * @param sender_info - a message system participant id of sender
				 */
				MessagePacker ( const MessageSystemParticipantId &sender_info )
					: sender_info ( sender_info )
				{
				}

				virtual ~MessagePacker () {};

				/**
				 * @brief Converts a concrete message class to a packed message
				 * @param msg - Concrete message object
				 * @return Packed message ready to be sent with a message dispatcher
				 */
				virtual PackedMessage packMessage ( const T& msg ) = 0;
			protected:
				MessageSystemParticipantId sender_info; ///< Id of sender
		};


	} /* namespace Core */
} /* namespace UnknownEngine */
