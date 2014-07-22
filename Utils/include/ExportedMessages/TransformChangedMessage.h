#pragma once

#include <string>

#include <InlineSpecification.h>
#include <MessageSystem/MessagePacker.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>
#include <Transform/Transform.h>
#include <Vectors/Vector3.h>
#include <Quaternion.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief Indicates that some simulation object changed its world transform
		 */
		struct TransformChangedMessage
		{
				UNKNOWNENGINE_INLINE
				constexpr static const char* getTypeName()
				{
					return "Engine.TransformChangedMessage";
				}

				Transform new_transform;
		};

		/**
		 * @brief Message packer for TransformChangedMessage
		 */
		class TransformChangedMessagePacker: public MessagePacker<TransformChangedMessage>
		{
			public:

				TransformChangedMessagePacker(const MessageSystemParticipantId &sender_info) :
						MessagePacker<TransformChangedMessage>(sender_info)
				{
					message_type_id = MessageDictionary::getSingleton()->getMessageTypeId(TransformChangedMessage::getTypeName());
				}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage(const TransformChangedMessage& msg) override
				{
					PackedMessage result(message_type_id, sender_info);

					Properties& properties = result.getProperties();
					properties.set<Transform>("new_transform", msg.new_transform);

					return result;
				}

			private:
				MessageType message_type_id;

		};

		/**
		 * @brief Message unpacker for TransformChangedMessage
		 */
		class TransformChangedMessageUnpacker: public MessageUnpacker<TransformChangedMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				LogMessage unpackMessage(const PackedMessage &msg)
						throw (InvalidMessageFormatException) override
				{
					TransformChangedMessage result;
					result.new_transform = msg.getProperties().get<Transform>("new_transform");
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */