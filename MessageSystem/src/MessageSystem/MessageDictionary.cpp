#include <stdafx.h>

#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		MessageDictionary* Singleton<MessageDictionary>::instance = nullptr;

		MessageDictionary::MessageDictionary ()
			: internal_dictionary ( "MessageDictionary.Dictionary", NUMERIC_IDENTIFIER_INITIAL_VALUE, INVALID_NUMERIC_IDENTIFIER, "<UNREGISTERED_MESSAGE_TYPE>" )
		{
			// TODO Auto-generated constructor stub
		}

		MessageType MessageDictionary::registerNewMessageType ( const char* message_type_name )
		{
			if ( messageTypeIsRegistered ( message_type_name ) ) return getMessageTypeId ( message_type_name );
			return internal_dictionary.registerNewValue ( message_type_name );
		}

		const char* MessageDictionary::getMessageTypeName ( const MessageType &type_id ) const 
		{
			return internal_dictionary.getValueByKey ( type_id ).c_str();
		}

		MessageType MessageDictionary::getMessageTypeId ( const char* type_name ) 
		{
			NumericIdentifierType type = internal_dictionary.getKeyByValue ( type_name );
			if(type == INVALID_NUMERIC_IDENTIFIER) type = registerNewMessageType(type_name);
			return type;
		}

		MessageDictionary::~MessageDictionary ()
		{
			// TODO Auto-generated destructor stub
		}

		bool MessageDictionary::messageTypeIsRegistered ( const MessageType &type_id ) const
		{
			return internal_dictionary.keyIsRegistered ( type_id );
		}

		bool MessageDictionary::messageTypeIsRegistered ( const char* type_name ) const
		{
			return internal_dictionary.valueIsRegistered ( type_name );
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
