#pragma once
/*
 * UpdateFrameMessage.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>

#include <MessageSystem/MessagePacker.h>
#include <InlineSpecification.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		struct LogMessage
		{
				UNKNOWNENGINE_INLINE
				constexpr static const char* getTypeName()
				{
					return "Engine.Log";
				}

				std::string log_entry;
		};

		class LogMessagePacker: public MessagePacker<LogMessage>
		{
			public:

				LogMessagePacker(SenderInfo sender_info) :
						MessagePacker<LogMessage>(sender_info)
				{
				}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage(const LogMessage& msg)
				{
					PackedMessage result(
							MessageDictionary::getSingleton()->getMessageTypeId(
									LogMessage::getTypeName()), sender_info);
					result.getProperties().set<std::string>("log_entry", msg.log_entry);
					return result;
				}

		};

		class LogMessageUnpacker: public MessageUnpacker<LogMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				LogMessage unpackMessage(const PackedMessage &msg)
						throw (InvalidMessageFormatException)
				{
					LogMessage result;
					result.log_entry = msg.getProperties().get<std::string>("log_entry");
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
