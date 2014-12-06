#pragma once

#include <MessageSystem_export.h>
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

				typedef Utils::Dictionary<NumericIdentifierType, std::string> InternalDictionaryType;
				
				MessageSystemParticipantDictionary ();
				virtual ~MessageSystemParticipantDictionary ();

				MESSAGESYSTEM_EXPORT
				NumericIdentifierType registerNewMessageParticipant ( const std::string &message_system_participant_name );

				MESSAGESYSTEM_EXPORT
				void unregisterMessageParticipant ( const std::string &message_system_participant_name );

				MESSAGESYSTEM_EXPORT
				NumericIdentifierType getMessageParticipantNameId ( const std::string &message_system_participant_name ) const;

				MESSAGESYSTEM_EXPORT
				bool messageSystemParticipantIsRegistered ( const std::string &message_system_participant_name ) const;

			private:
				InternalDictionaryType internal_dictionary;

		};

#ifdef _MSC_VER
#ifndef MessageSystem_EXPORTS
		extern template class MESSAGESYSTEM_EXPORT Singleton<MessageSystemParticipantDictionary>;
#else
		template class MESSAGESYSTEM_EXPORT Singleton<MessageSystemParticipantDictionary>;
#endif
#endif

	} /* namespace Core */
} /* namespace UnknownEngine */
