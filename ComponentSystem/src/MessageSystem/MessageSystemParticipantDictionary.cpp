/*
 * MessageDictionary.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <stdafx.h>

#include <MessageSystem/MessageSystemParticipantDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		MessageSystemParticipantDictionary* Singleton<MessageSystemParticipantDictionary>::instance = nullptr;

		MessageSystemParticipantDictionary::MessageSystemParticipantDictionary ()
				: internal_dictionary(NUMERIC_IDENTIFIER_INITIAL_VALUE, INVALID_NUMERIC_IDENTIFIER)
		{
		}

		NumericIdentifierType MessageSystemParticipantDictionary::registerNewMessageParticipant ( const std::string &message_system_participant_name )
		{
			return internal_dictionary.registerNewValue(message_system_participant_name);
		}

		void MessageSystemParticipantDictionary::unregisterMessageParticipant(const std::string &message_system_participant_name)
		{
			internal_dictionary.deleteEntryByValue(message_system_participant_name);
		}

		NumericIdentifierType MessageSystemParticipantDictionary::getMessageParticipantNameId ( const std::string &message_system_participant_name ) const
		{
			return internal_dictionary.getKeyByValue(message_system_participant_name);
		}

		bool MessageSystemParticipantDictionary::messageSystemParticipantIsRegistered(const std::string &message_system_participant_name) const
		{
			return internal_dictionary.valueIsRegistered(message_system_participant_name);
		}

		MessageSystemParticipantDictionary::~MessageSystemParticipantDictionary ()
		{
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
