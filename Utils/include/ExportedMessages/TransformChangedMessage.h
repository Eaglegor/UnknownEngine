#pragma once

#include <string>

#include <InlineSpecification.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageUnpacker.h>
#include <MessageSystem/TypeCachingMessagePacker.h>
#include <Transform/Transform.h>
#include <Vectors/Vector3.h>
#include <Quaternion.h>

namespace UnknownEngine
{
	namespace Core
	{

		class TransformChangedMessagePacker;
		class TransformChangedMessageUnpacker;

		/**
		 * @brief Indicates that some simulation object changed its world transform
		 */
		struct TransformChangedMessage
		{

			typedef TransformChangedMessagePacker PackerClass;
			typedef TransformChangedMessageUnpacker UnpackerClass;

			UNKNOWNENGINE_INLINE
			static std::string getTypeName()
			{
				return "Engine.TransformChangedMessage";
			}

			Transform new_transform;
		};

		/**
		 * @brief Message packer for TransformChangedMessage
		 */
		class TransformChangedMessagePacker: public TypeCachingMessagePacker<TransformChangedMessage>
		{
			public:

				TransformChangedMessagePacker ( const MessageSystemParticipantId &sender_info ) :
					TypeCachingMessagePacker<TransformChangedMessage> ( sender_info )
				{
				}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage ( const TransformChangedMessage& msg ) override
				{
					PackedMessage result ( getMessageType(), sender_info );

					Properties& properties = result.getProperties();
					properties.set<Transform> ( "new_transform", msg.new_transform );

					return result;
				}

		};

		/**
		 * @brief Message unpacker for TransformChangedMessage
		 */
		class TransformChangedMessageUnpacker: public MessageUnpacker<TransformChangedMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				TransformChangedMessage unpackMessage ( const PackedMessage &msg ) override
				{
					TransformChangedMessage result;
					result.new_transform = msg.getProperties().get<Transform> ( "new_transform" );
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
