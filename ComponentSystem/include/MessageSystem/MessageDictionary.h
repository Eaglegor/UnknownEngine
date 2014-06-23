#pragma once
/*
 * MessageDictionary.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <unordered_map>
#include <MessageSystem/PackedMessage.h>
#include <Singleton.h>

namespace UnknownEngine
{
	namespace Core
	{

		class MessageDictionary : public Singleton<MessageDictionary>
		{
			public:
				MessageDictionary ();
				virtual ~MessageDictionary ();
				ComponentMessageTypeId registerNewMessageType(std::string message_type_name);
				bool messageTypeIsRegistered(ComponentMessageTypeId type_id);
				bool messageTypeIsRegistered(std::string type_name);
				std::string getMessageTypeName(ComponentMessageTypeId type_id);
				ComponentMessageTypeId getMessageTypeId(std::string type_name);

			private:

				ComponentMessageTypeId last_used_type_id;

				std::unordered_map<std::string, ComponentMessageTypeId> name_id_mapping;
				std::unordered_map<ComponentMessageTypeId, std::string> id_name_mapping;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
