#pragma once
/*
 * UpdateFrameMessage.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>

#include <InlineSpecification.h>
#include <MessageSystem/TypeCachingMessagePacker.h>
#include <MessageSystem/MessageUnpacker.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		class StopEngineActionMessagePacker;
		class StopEngineActionMessageUnpacker;

		/**
		 * @brief Engine stop command
		 *
		 * Stops engine
		 */

		struct StopEngineActionMessage
		{

			typedef StopEngineActionMessagePacker PackerClass;
			typedef StopEngineActionMessageUnpacker UnpackerClass;

			UNKNOWNENGINE_INLINE
			static std::string getTypeName()
			{
				return "Engine.StopEngineActionMessage";
			}
		};

		/**
		 * @brief Message packer for StopEngineActionMessage
		 */
		class StopEngineActionMessagePacker: public TypeCachingMessagePacker<StopEngineActionMessage>
		{
			public:

				StopEngineActionMessagePacker ( const MessageSystemParticipantId &sender_info ) :
					TypeCachingMessagePacker<StopEngineActionMessage> ( sender_info )
				{
				}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage ( const StopEngineActionMessage &msg ) override
				{
					return PackedMessage (getMessageType(), sender_info );
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
				 override
				{
					return StopEngineActionMessage();
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
