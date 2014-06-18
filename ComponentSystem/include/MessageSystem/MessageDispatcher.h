#pragma once
/*
 * MessageDispatcher.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <unordered_map>

#include <MessageSystem/Message.h>
#include <MessageSystem/IMessageListener.h>

namespace UnknownEngine
{
	namespace Core
	{

		class MessageDispatcher
		{
			public:
				MessageDispatcher ();
				virtual ~MessageDispatcher ();

				void addListener(ComponentMessageTypeId message_type_id, IMessageListener* listener);
				void addListener(std::string message_type_name, IMessageListener* listener);

				void removeListener(ComponentMessageTypeId message_type_id, IMessageListener* listener);
				void removeListener(std::string message_type_name, IMessageListener* listener);
				void removeListener(IMessageListener* listener);

				void deliverMessage(Message* msg);

			private:
				std::unordered_map<ComponentMessageTypeId, IMessageListener*> listeners;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
