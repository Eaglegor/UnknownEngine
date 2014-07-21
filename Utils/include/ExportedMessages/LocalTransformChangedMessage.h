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
#include <Transform/Transform.h>
#include <Vectors/Vector3.h>
#include <Quaternion.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief Indicates that the transform of some subobject is changed
		 *
		 * \tparam - type of subobject identifier
		 * */
		template<typename SubObjectIdentifierType>
		struct LocalTransformChangedMessage
		{
				UNKNOWNENGINE_INLINE
				constexpr static const char* getTypeName()
				{
					return "Engine.TransformChanged";
				}

				Transform new_transform;
				SubObjectIdentifierType sub_object_identifier; ///< Identifier of subobject (number of part, local name etc.)
		};

		/**
		 * @brief Message packer for TransformChangedMessageUnpacker
		 */
		template<typename SubObjectIdentifierType>
		class TransformChangedMessagePacker: public MessagePacker<LocalTransformChangedMessage<SubObjectIdentifierType> >
		{
			public:

				TransformChangedMessagePacker(const MessageSystemParticipantId &sender_info) :
						MessagePacker<LocalTransformChangedMessage>(sender_info)
				{
					message_type_id = MessageDictionary::getSingleton()->getMessageTypeId(LogMessage::getTypeName());
				}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage(const LocalTransformChangedMessage& msg) override
				{
					PackedMessage result(message_type_id, sender_info);

					Properties& properties = result.getProperties();
					properties.set<Transform>("new_transform", msg.new_transform);
					properties.set<SubObjectIdentifierType>("sub_object_identifier", msg.sub_object_identifier);

					return result;
				}

			private:
				MessageType message_type_id;

		};

		/**
		 * @brief Message unpacker for TransformChangedMessageUnpacker
		 */
		template<typename SubObjectIdentifierType>
		class TransformChangedMessageUnpacker: public MessageUnpacker<LocalTransformChangedMessage<SubObjectIdentifierType> >
		{
			public:

				UNKNOWNENGINE_INLINE
				LogMessage unpackMessage(const PackedMessage &msg)
						throw (InvalidMessageFormatException) override
				{
					LocalTransformChangedMessage result;
					result.new_transform = msg.getProperties().get<Transform>("new_transform");
					result.sub_object_identifier = msg.getProperties().get<SubObjectIdentifierType>("sub_object_identifier");
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
