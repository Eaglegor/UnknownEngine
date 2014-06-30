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
				: last_used_id ( 0 )
		{
			// TODO Auto-generated constructor stub

		}

		NumericIdentifierType MessageSystemParticipantDictionary::registerMessageParticipant ( const std::string &message_system_participant_name )
		{
			auto iter = name_id_mapping.find(message_system_participant_name);
			if(iter != name_id_mapping.end()) return iter->second;
			++last_used_id;
			name_id_mapping.insert ( std::make_pair ( message_system_participant_name, last_used_id ) );
			return last_used_id;
		}

		void MessageSystemParticipantDictionary::unregisterMessageParticipant(const std::string &message_system_participant_name)
		{
			auto iter = name_id_mapping.find(message_system_participant_name);
			if(iter != name_id_mapping.end()) name_id_mapping.erase(iter);
		}

		NumericIdentifierType MessageSystemParticipantDictionary::getMessageParticipantNameId ( const std::string &message_system_participant_name ) const
		{
			auto iter = name_id_mapping.find(message_system_participant_name);
			if(iter != name_id_mapping.end()) return iter->second;
			return INVALID_NUMERIC_IDENTIFIER;
		}

		MessageSystemParticipantDictionary::~MessageSystemParticipantDictionary ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
