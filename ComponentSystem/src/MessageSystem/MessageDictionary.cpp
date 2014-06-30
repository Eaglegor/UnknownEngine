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
				: last_used_type_id ( 0 )
		{
			// TODO Auto-generated constructor stub

		}

		NumericIdentifierType MessageDictionary::registerNewMessageType ( const std::string &message_type_name )
		{
			if ( messageTypeIsRegistered ( message_type_name ) ) return getMessageTypeId ( message_type_name );
			++last_used_type_id;
			id_name_mapping.insert ( std::make_pair ( last_used_type_id, message_type_name ) );
			name_id_mapping.insert ( std::make_pair ( message_type_name, last_used_type_id ) );
			return last_used_type_id;
		}

		std::string MessageDictionary::getMessageTypeName ( const NumericIdentifierType &type_id ) const
		{
			if ( this->messageTypeIsRegistered ( type_id ) ) return id_name_mapping.find ( type_id )->second;
			else return "UknownMessage";
		}

		NumericIdentifierType MessageDictionary::getMessageTypeId ( const std::string &type_name ) const
		{
			if ( this->messageTypeIsRegistered ( type_name ) )
			{
				return name_id_mapping.find ( type_name )->second;
			}

			else
			{
				return INVALID_NUMERIC_IDENTIFIER;
			}
		}

		MessageDictionary::~MessageDictionary ()
		{
			// TODO Auto-generated destructor stub
		}

		bool MessageDictionary::messageTypeIsRegistered ( const NumericIdentifierType &type_id ) const
		{
			return id_name_mapping.find ( type_id ) != id_name_mapping.end();
		}

		bool MessageDictionary::messageTypeIsRegistered ( const std::string &type_name ) const
		{
			return name_id_mapping.find ( type_name ) != name_id_mapping.end();
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
