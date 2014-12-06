#pragma once
/*
 * MessageDictionary.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <MessageSystem_export.h>
#include <unordered_map>
#include <Singleton.h>
#include <NumericIdentifierType.h>
#include <Dictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief The address book for the objects using message bus (MessageDispatcher)
		 *
		 * This class holds "object name" - "numeric id" mapping for all objects. Using such class guarantees that
		 * the name of newly created message system participant will be unique across the whole bus.
		 *
		 */
		class MessageSystemParticipantDictionary : public Singleton<MessageSystemParticipantDictionary>
		{
			public:

				typedef Utils::Dictionary<NumericIdentifierType, std::string> InternalDictionaryType;
				
				MessageSystemParticipantDictionary ();
				virtual ~MessageSystemParticipantDictionary ();

				/**
				 * @brief Registers the new object at the message bus by name asigning it a numeric address id
				 * @param message_system_participant_name - Object name to be registered
				 * @return Assigned numeric identifier
				 */
				MESSAGESYSTEM_EXPORT
				NumericIdentifierType registerNewMessageParticipant ( const std::string &message_system_participant_name );

				/**
				 * @brief Removes the object name from a bus
				 * @param message_system_participant_name - Object name to be unregistered
				 */
				MESSAGESYSTEM_EXPORT
				void unregisterMessageParticipant ( const std::string &message_system_participant_name );

				/**
				 * @brief Returns the numeric address id for registered object name
				 * @param message_system_participant_name - Object name to get the id for
				 * @return Numeric address identifier of object
				 */
				MESSAGESYSTEM_EXPORT
				NumericIdentifierType getMessageParticipantNameId ( const std::string &message_system_participant_name ) const;

				/**
				 * @brief Checks if some object name is registered
				 * @param message_system_participant_name - Object name to check for
				 * @return true if object name is registered
				 */
				MESSAGESYSTEM_EXPORT
				bool messageSystemParticipantIsRegistered ( const std::string &message_system_participant_name ) const;

			private:
				InternalDictionaryType internal_dictionary; ///< Internal dictionary implementation

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
