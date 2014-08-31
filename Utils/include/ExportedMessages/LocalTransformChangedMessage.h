#pragma once

#include <string>

#include <InlineSpecification.h>
#include <MessageSystem/MessageUnpacker.h>
#include <MessageSystem/TypeCachingMessagePacker.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>
#include <Transform/Transform.h>
#include <Vectors/Vector3.h>
#include <Quaternion.h>

namespace UnknownEngine
{
	namespace Core
	{
		template<typename SubObjectIdentifierType>
		class TransformChangedMessagePacker;

		template<typename SubObjectIdentifierType>
		class TransformChangedMessageUnpacker;

		/**
		 * @brief Indicates that some subobject changed its local transform in CS of parent object
		 *
		 * \tparam - type of subobject identifier (string, index, guid, etc.)
		 * */
		template<typename SubObjectIdentifierType>
		struct LocalTransformChangedMessage
		{

			typedef TransformChangedMessagePacker<SubObjectIdentifierType> PackerClass;
			typedef TransformChangedMessageUnpacker<SubObjectIdentifierType> UnpackerClass;

			UNKNOWNENGINE_INLINE
			static std::string getTypeName()
			{
				return "Engine.LocalTransformChangedMessage";
			}

			Transform new_transform;
			SubObjectIdentifierType sub_object_identifier; ///< Identifier of subobject (number of part, local name etc.)
		};

		/**
		 * @brief Message packer for TransformChangedMessageUnpacker
		 */
		template<typename SubObjectIdentifierType>
		class TransformChangedMessagePacker: public TypeCachingMessagePacker<LocalTransformChangedMessage<SubObjectIdentifierType> >
		{
			public:

				TransformChangedMessagePacker ( const MessageSystemParticipantId &sender_info ) :
					TypeCachingMessagePacker<LocalTransformChangedMessage> ( sender_info )
				{
				}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage ( const LocalTransformChangedMessage& msg ) override
				{
					PackedMessage result ( getMessageType(), sender_info );

					Properties& properties = result.getProperties();
					properties.set<Transform> ( "new_transform", msg.new_transform );
					properties.set<SubObjectIdentifierType> ( "sub_object_identifier", msg.sub_object_identifier );

					return result;
				}

		};

		/**
		 * @brief Message unpacker for TransformChangedMessageUnpacker
		 */
		template<typename SubObjectIdentifierType>
		class TransformChangedMessageUnpacker: public MessageUnpacker<LocalTransformChangedMessage<SubObjectIdentifierType> >
		{
			public:

				UNKNOWNENGINE_INLINE
				LogMessage unpackMessage ( const PackedMessage &msg )
				throw ( InvalidMessageFormatException ) override
				{
					LocalTransformChangedMessage result;
					result.new_transform = msg.getProperties().get<Transform> ( "new_transform" );
					result.sub_object_identifier = msg.getProperties().get<SubObjectIdentifierType> ( "sub_object_identifier" );
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
