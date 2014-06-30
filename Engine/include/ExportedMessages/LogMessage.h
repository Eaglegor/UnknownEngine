#pragma once
/*
 * UpdateFrameMessage.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>

#include <InlineSpecification.h>
#include <MessageSystem/MessagePacker.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		struct LogMessage
		{

				enum Severity
				{
					LOG_SEVERITY_ERROR,
					LOG_SEVERITY_WARNING,
					LOG_SEVERITY_INFO,
					LOG_SEVERITY_DEBUG
				};

				UNKNOWNENGINE_INLINE
				constexpr static const char* getTypeName()
				{
					return "Engine.Log";
				}

				std::string log_entry;
				Severity severity;
		};

		class LogMessagePacker: public MessagePacker<LogMessage>
		{
			public:

				LogMessagePacker(MessageSystemParticipantId sender_info) :
						MessagePacker<LogMessage>(sender_info)
				{
				}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage(const LogMessage& msg) override
				{
					PackedMessage result(
							MessageDictionary::getSingleton()->getMessageTypeId(
									LogMessage::getTypeName()), sender_info);
					result.getProperties().set<std::string>("log_entry", msg.log_entry);
					result.getProperties().set<LogMessage::Severity>("severity", msg.severity);
					return result;
				}

		};

		class LogMessageUnpacker: public MessageUnpacker<LogMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				LogMessage unpackMessage(const PackedMessage &msg)
						throw (InvalidMessageFormatException) override
				{
					LogMessage result;
					result.log_entry = msg.getProperties().get<std::string>("log_entry");
					result.severity = msg.getProperties().get<LogMessage::Severity>("severity");
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
