#include <stdafx.h>

#include <MessageSystem/MessageSystemParticipantDictionary.h>

#define LOG(e) std::cout << e << std::endl

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		MessageSystemParticipantDictionary* Singleton<MessageSystemParticipantDictionary>::instance = nullptr;

		MessageSystemParticipantDictionary::MessageSystemParticipantDictionary ()
			: internal_dictionary ( "MessageSystemParticipantDictionary.Dictionary", NUMERIC_IDENTIFIER_INITIAL_VALUE, INVALID_NUMERIC_IDENTIFIER )
		{
		}

		NumericIdentifierType MessageSystemParticipantDictionary::registerNewMessageParticipant ( const std::string &message_system_participant_name )
		{
			try
			{
				return internal_dictionary.registerNewValue ( message_system_participant_name );
			}
			catch ( const InternalDictionaryType::ValueAlreadyExists& e )
			{
				LOG ( "Error while adding message system participant: " + message_system_participant_name );
				throw e;
			}
		}

		void MessageSystemParticipantDictionary::unregisterMessageParticipant ( const std::string &message_system_participant_name )
		{
			internal_dictionary.deleteEntryByValue ( message_system_participant_name );
		}

		NumericIdentifierType MessageSystemParticipantDictionary::getMessageParticipantNameId ( const std::string &message_system_participant_name ) const
		{
			return internal_dictionary.getKeyByValue ( message_system_participant_name );
		}

		bool MessageSystemParticipantDictionary::messageSystemParticipantIsRegistered ( const std::string &message_system_participant_name ) const
		{
			return internal_dictionary.valueIsRegistered ( message_system_participant_name );
		}

		MessageSystemParticipantDictionary::~MessageSystemParticipantDictionary ()
		{
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
