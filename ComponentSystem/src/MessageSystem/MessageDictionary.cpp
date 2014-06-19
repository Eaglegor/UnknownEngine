/*
 * MessageDictionary.cpp
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <MessageSystem/MessageDictionary.h>
#include <iostream>

namespace UnknownEngine
{
	namespace Core
	{

		MessageDictionary* MessageDictionary::instance = nullptr;

		MessageDictionary::MessageDictionary ()
				: last_used_type_id ( 0 )
		{
			// TODO Auto-generated constructor stub

		}

		ComponentMessageTypeId MessageDictionary::registerNewMessageType ( std::string message_type_name )
		{
			if ( messageTypeIsRegistered ( message_type_name ) ) return getMessageTypeId ( message_type_name );
			++last_used_type_id;
			id_name_mapping.insert ( std::make_pair ( last_used_type_id, message_type_name ) );
			name_id_mapping.insert ( std::make_pair ( message_type_name, last_used_type_id ) );
			return last_used_type_id;
		}

		std::string MessageDictionary::getMessageTypeName ( ComponentMessageTypeId type_id )
		{
			if ( this->messageTypeIsRegistered ( type_id ) ) return id_name_mapping.find ( type_id )->second;
			else return "UknownMessage";
		}

		ComponentMessageTypeId MessageDictionary::getMessageTypeId ( std::string type_name )
		{
			if ( this->messageTypeIsRegistered ( type_name ) )
			{
				return name_id_mapping.find ( type_name )->second;
			}

			else
			{
				return UNKNOWN_MESSAGE_TYPE;
			}
		}

		MessageDictionary* MessageDictionary::getSingleton ()
		{
			if ( instance == nullptr )
			{
				instance = new MessageDictionary ();
			}
			return instance;
		}

		MessageDictionary::~MessageDictionary ()
		{
			// TODO Auto-generated destructor stub
		}

		bool MessageDictionary::messageTypeIsRegistered ( ComponentMessageTypeId type_id )
		{
			return id_name_mapping.find ( type_id ) != id_name_mapping.end ();
		}

		bool MessageDictionary::messageTypeIsRegistered ( std::string type_name )
		{
			return name_id_mapping.find ( type_name ) != name_id_mapping.end ();
		}

		void MessageDictionary::initInstance ( MessageDictionary* dictionary )
		{
			if ( instance == nullptr ) instance = dictionary;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
