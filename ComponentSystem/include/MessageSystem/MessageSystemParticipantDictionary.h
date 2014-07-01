#pragma once
/*
 * MessageDictionary.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <unordered_map>
#include <Singleton.h>
#include <NumericIdentifierType.h>
#include <Dictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		class MessageSystemParticipantDictionary : public Singleton<MessageSystemParticipantDictionary>
		{
			public:
				MessageSystemParticipantDictionary ();
				virtual ~MessageSystemParticipantDictionary ();

				NumericIdentifierType registerMessageParticipant(const std::string &message_system_participant_name);
				void unregisterMessageParticipant(const std::string &message_system_participant_name);
				NumericIdentifierType getMessageParticipantNameId(const std::string &message_system_participant_name) const;

			private:
				Utils::Dictionary<NumericIdentifierType, std::string> internal_dictionary;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
