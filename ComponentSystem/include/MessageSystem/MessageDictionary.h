#pragma once
/*
 * MessageDictionary.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <ComponentSystem_export.h>
#include <unordered_map>
#include <Singleton.h>
#include <NumericIdentifierType.h>
#include <MessageSystem/MessageType.h>
#include <Dictionary.h>

namespace UnknownEngine
{

	namespace Core
	{

		/**
		 *  @brief Class that manages assigning numeric identifiers to string message types

			### Concept
			Sending/receiving messages is the expected way of communication between components.
			Message dispatching is done firstly by message type.
			The machine-friendly message type should be integral (e.g. enum).
			But we don't know most of the message types which will be sent/received from subsystems.
			We can't push users to use simple integer identifiers, because it could raise type identifier conflicts between independently developed modules.
			That's why we use a string identifiers for message types. But strings are not very friendly in search operations (even using hashing).
			Therefore we assign a numeric type identifier to be used by \ref MessageDispatcher "message dispatcher" to the string message type from subsystem.
			Now when we want to find a listener for a message we just search for a simple integral value in a listeners map getting a performance boost.

			### Usage
			If a subsystem wants to register a message it calls a registerNewMessageType() method. After that A numeric identifier of message type can be
			accessed by the call to getMessageTypeId() method. This numeric type id can be cached by sender (expected way is to cache it in the message packer).

		 */
		class MessageDictionary : public Singleton<MessageDictionary>
		{

			public:

				typedef Utils::Dictionary<MessageType, std::string> InternalDictionaryType;

				/**
				 * @brief Default constructor.
				 *
				 * Is called by Engine
				 *
				 */
				COMPONENTSYSTEM_EXPORT
				MessageDictionary ();

				COMPONENTSYSTEM_EXPORT
				virtual ~MessageDictionary ();

				/**
				 * @brief Registers a new string message type and assigns it a numeric identifier
				 * @param message_type_name - The name of message type to be registered
				 * @throw Utils::Dictionary::ValueAlreadyExists - Is thrown when trying to insert already known type
				 * @return Assigned numeric identifier
				 */
				COMPONENTSYSTEM_EXPORT
				MessageType registerNewMessageType(const std::string &message_type_name);

				/**
				 * @brief Checks if message type is registered
				 * @param type_id - Numeric identifier of message type
				 * @return true if registered
				 */
				COMPONENTSYSTEM_EXPORT
				bool messageTypeIsRegistered(const MessageType &type_id) const;

				/**
				 * @brief Checks if message type is registered
				 * @param type_name - Name of message type
				 * @return true if registered
				 */
				COMPONENTSYSTEM_EXPORT
				bool messageTypeIsRegistered(const std::string &type_name) const;

				/**
				 * @brief Returns a message type name if the message type id is known
				 * @param type_id - Message type id for which we have to get the name
				 * @return A message type name
				 * @throw Utils::Dictionary::EntryNotFoundInDictionary - Is thrown if there is no such message type identifier registered
				 */
				COMPONENTSYSTEM_EXPORT
				std::string getMessageTypeName(const MessageType &type_id) const throw(InternalDictionaryType::EntryNotFoundInDictionary);

				/**
				 * @brief Returns a message type id if the message type name is known
				 * @param type_name - Message type name for which we have to get the id
				 * @return A message type id
				 * @throw Utils::Dictionary::EntryNotFoundInDictionary - Is thrown if there is no such message type identifier registered
				 */
				COMPONENTSYSTEM_EXPORT
				MessageType getMessageTypeId(const std::string &type_name) const throw (InternalDictionaryType::EntryNotFoundInDictionary);

			private:
				InternalDictionaryType internal_dictionary; ///< Internal dictionary implementation

		};

		extern template class COMPONENTSYSTEM_EXPORT Singleton<MessageDictionary>;

	} /* namespace Core */
} /* namespace UnknownEngine */
