#pragma once

#include <InlineSpecification.h>
#include <MessageSystem/MessageType.h>
#include <MessageSystem/MessagePacker.h>
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
		class EngineStartedMessagePacker: public MessagePacker<EngineStartedMessage>
		{
			public:

				EngineStartedMessagePacker ( const MessageSystemParticipantId &sender_info ) :
					MessagePacker<EngineStartedMessage> ( sender_info )
				{
					message_type = MessageDictionary::getSingleton()->getMessageTypeId ( EngineStartedMessage::getTypeName() );
				}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage ( const EngineStartedMessage& msg ) override
				{
					return PackedMessage ( message_type, sender_info );
				}

			private:
				MessageType message_type;

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
