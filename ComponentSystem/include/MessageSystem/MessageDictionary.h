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
#include <MessageSystem/MessageType.h>
#include <Dictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		class MessageDictionary : public Singleton<MessageDictionary>
		{
			public:
				MessageDictionary ();
				virtual ~MessageDictionary ();

				MessageType registerNewMessageType(const std::string &message_type_name);
				bool messageTypeIsRegistered(const MessageType &type_id) const;
				bool messageTypeIsRegistered(const std::string &type_name) const;
				std::string getMessageTypeName(const MessageType &type_id) const;
				MessageType getMessageTypeId(const std::string &type_name) const;

			private:
				Utils::Dictionary<MessageType, std::string> internal_dictionary;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
