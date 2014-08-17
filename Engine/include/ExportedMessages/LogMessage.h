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

		/**
		 * @brief Log entry message
		 *
		 * Just a log message with specified severity.
		 * Purposed to be catched by logging subsystems.
		 * Recommended to be broadcasted to be catched by all logging subsystems.
		 */

		struct LogMessage
		{
			
			enum class Severity : int
			{
			    LOG_SEVERITY_NONE = 0,
			    LOG_SEVERITY_ERROR = 1,
			    LOG_SEVERITY_WARNING = 2,
			    LOG_SEVERITY_INFO = 3,
			    LOG_SEVERITY_DEBUG = 4
			};

			UNKNOWNENGINE_INLINE
			static std::string getTypeName()
			{
				return "Engine.LogMessage";
			}

			std::string log_entry;
			Severity severity;
		};

		/**
		 * @brief Message packer for LogMessage
		 */
		class LogMessagePacker: public MessagePacker<LogMessage>
		{
			public:

				LogMessagePacker ( const MessageSystemParticipantId &sender_info ) :
					MessagePacker<LogMessage> ( sender_info )
				{
				}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage ( const LogMessage& msg ) override
				{
					PackedMessage result (
					    MessageDictionary::getSingleton()->getMessageTypeId (
					        LogMessage::getTypeName() ), sender_info );
					result.getProperties().set<std::string> ( "log_entry", msg.log_entry );
					result.getProperties().set<LogMessage::Severity> ( "severity", msg.severity );
					return result;
				}

		};

		/**
		 * @brief Message unpacker for LogMessage
		 */
		class LogMessageUnpacker: public MessageUnpacker<LogMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				LogMessage unpackMessage ( const PackedMessage &msg )
				throw ( InvalidMessageFormatException ) override
				{
					LogMessage result;
					result.log_entry = msg.getProperties().get<std::string> ( "log_entry" );
					result.severity = msg.getProperties().get<LogMessage::Severity> ( "severity" );
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
