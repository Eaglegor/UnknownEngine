#pragma once
/*
 * MessageDictionary.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <unordered_map>

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Core
	{

		class MessageDictionary
		{
			public:

				ComponentMessageTypeId registerNewMessageType(std::string message_type_name);
				bool messageTypeIsRegistered(ComponentMessageTypeId type_id);
				bool messageTypeIsRegistered(std::string type_name);
				std::string getMessageTypeName(ComponentMessageTypeId type_id);
				ComponentMessageTypeId getMessageTypeId(std::string type_name);

				static MessageDictionary* getSingleton();
				static void initInstance(MessageDictionary* dictionary);

			private:

				static MessageDictionary* instance;

				ComponentMessageTypeId last_used_type_id;

				std::unordered_map<std::string, ComponentMessageTypeId> name_id_mapping;
				std::unordered_map<ComponentMessageTypeId, std::string> id_name_mapping;

				MessageDictionary ();
				virtual ~MessageDictionary ();

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
