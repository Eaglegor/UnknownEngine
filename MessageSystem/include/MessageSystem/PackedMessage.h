#pragma once
/*
 * Message.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <MessageSystem_export.h>
#include <string>
#include <boost/any.hpp>

#include <InlineSpecification.h>
#include <MessageSystem/MessageType.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <MessageSystem/MessageDictionary.h>

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
				 * @brief Constructor querying message dictionary for message type
				 * @param message - concrete typed message
				 * @param sender_info - information about message sender
				 */
				template<typename T>
				PackedMessage ( const T& message):
				message_type_id ( MESSAGE_TYPE_ID(T::getTypeName()) ), 
				message_container(message)
				{
				}

				/**
				 * @brief Constructor without query to message dictionary for message type (faster but you need to know message_type_id)
				 * @param message - concrete typed message
				 * @param message_type_id - numeric identifier of message type
				 * @param sender_info - information about message sender
				 */
				template<typename T>
				PackedMessage ( const T& message, MessageType message_type ):
				message_type_id ( message_type ), 
				message_container(message)
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
				 * @brief Returns concrete message packed to this container
				 * @return Concrete message class specified by a template
				 * @throw boost::bad_any_cast if requested message type is not matching with stored
				 */
				template<typename T>
				UNKNOWNENGINE_INLINE
				const T& get() const
				{
					return boost::any_cast<const T&>(message_container);
				}
				
			private:
				MessageType message_type_id; ///< Numeric message type identifier
				boost::any message_container;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
