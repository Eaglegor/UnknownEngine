/*
 * MessageDictionary.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <stdafx.h>

#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		MessageDictionary* Singleton<MessageDictionary>::instance = nullptr;

		MessageDictionary::MessageDictionary ()
			: internal_dictionary ( "MessageDictionary.Dictionary", NUMERIC_IDENTIFIER_INITIAL_VALUE, INVALID_NUMERIC_IDENTIFIER )
		{
			// TODO Auto-generated constructor stub
		}

		MessageType MessageDictionary::registerNewMessageType ( const std::string &message_type_name )
		{
			if ( messageTypeIsRegistered ( message_type_name ) ) return getMessageTypeId ( message_type_name );
			return internal_dictionary.registerNewValue ( message_type_name );
		}

		std::string MessageDictionary::getMessageTypeName ( const MessageType &type_id ) const throw ( InternalDictionaryType::EntryNotFoundInDictionary )
		{
			return internal_dictionary.getValueByKey ( type_id );
		}

		MessageType MessageDictionary::getMessageTypeId ( const std::string &type_name ) const throw ( InternalDictionaryType::EntryNotFoundInDictionary )
		{
			return internal_dictionary.getKeyByValue ( type_name );
		}

		MessageDictionary::~MessageDictionary ()
		{
			// TODO Auto-generated destructor stub
		}

		bool MessageDictionary::messageTypeIsRegistered ( const MessageType &type_id ) const
		{
			return internal_dictionary.keyIsRegistered ( type_id );
		}

		bool MessageDictionary::messageTypeIsRegistered ( const std::string &type_name ) const
		{
			return internal_dictionary.valueIsRegistered ( type_name );
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
