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
		 * @brief Engine stop command
		 *
		 * Stops engine
		 */

		struct StopEngineActionMessage
		{
			UNKNOWNENGINE_INLINE
			static std::string getTypeName()
			{
				return "Engine.StopEngineActionMessage";
			}
		};

		/**
		 * @brief Message packer for StopEngineActionMessage
		 */
		class StopEngineActionMessagePacker: public MessagePacker<StopEngineActionMessage>
		{
			public:

				StopEngineActionMessagePacker ( const MessageSystemParticipantId &sender_info ) :
					MessagePacker<StopEngineActionMessage> ( sender_info )
				{
				}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage ( const StopEngineActionMessage &msg ) override
				{
					return PackedMessage (
					           MessageDictionary::getSingleton()->getMessageTypeId (
					               StopEngineActionMessage::getTypeName() ), sender_info );
				}

		};

		/**
		 * @brief Message unpacker for StopEngineActionMessage
		 */
		class StopEngineActionMessageUnpacker: public MessageUnpacker<StopEngineActionMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				StopEngineActionMessage unpackMessage ( const PackedMessage &msg )
				throw ( InvalidMessageFormatException ) override
				{
					return StopEngineActionMessage();
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
