#pragma once

#include <InlineSpecification.h>
#include <MessageSystem/MessageType.h>
#include <MessageSystem/MessageUnpacker.h>
#include <MessageSystem/TypeCachingMessagePacker.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineStartedMessagePacker;
		class EngineStartedMessageUnpacker;

		/**
		 * @brief Indicator of engine start
		 *
		 */
		struct EngineStartedMessage
		{
			typedef EngineStartedMessagePacker PackerClass;
			typedef EngineStartedMessageUnpacker UnpackerClass;

			UNKNOWNENGINE_INLINE
			static std::string getTypeName()
			{
				return "Engine.EngineStartedMessage";
			}
		};

		/**
		 * @brief Message packer for EngineStartedMessage
		 */
		class EngineStartedMessagePacker: public TypeCachingMessagePacker<EngineStartedMessage>
		{
			public:

				EngineStartedMessagePacker ( const MessageSystemParticipantId &sender_info ) :
					TypeCachingMessagePacker<EngineStartedMessage> ( sender_info )
				{}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage ( const EngineStartedMessage& msg ) override
				{
					return PackedMessage ( getMessageType(), sender_info );
				}

		};

		/**
		 * @brief Message unpacker for EngineStartedMessage
		 */
		class EngineStartedMessageUnpacker: public MessageUnpacker<EngineStartedMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				EngineStartedMessage unpackMessage ( const PackedMessage &msg )
				throw ( InvalidMessageFormatException ) override
				{
					return EngineStartedMessage();
				}

		};
	}
}
