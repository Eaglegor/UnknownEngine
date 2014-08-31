#pragma once

#include <InlineSpecification.h>
#include <Vectors/Vector3.h>
#include <MessageSystem/MessageUnpacker.h>
#include <MessageSystem/TypeCachingMessagePacker.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class CameraLookAtActionMessagePacker;
		class CameraLookAtActionMessageUnpacker;

		/**
		 * @brief Command for camera to look at some position
		 *
		 */
		struct CameraLookAtActionMessage
		{

			typedef CameraLookAtActionMessagePacker PackerClass;
			typedef CameraLookAtActionMessageUnpacker UnpackerClass;

			UNKNOWNENGINE_INLINE
			static std::string getTypeName()
			{
				return "Graphics.CameraLookAtActionMessage";
			}

			Math::Vector3 look_at_position;
		};

		/**
		 * @brief Message packer for UpdateFrameMessage
		 */
		class CameraLookAtActionMessagePacker: public Core::TypeCachingMessagePacker<CameraLookAtActionMessage>
		{
			public:

				CameraLookAtActionMessagePacker ( Core::MessageSystemParticipantId sender_info ) :
					Core::TypeCachingMessagePacker<CameraLookAtActionMessage> ( sender_info )
				{
				}

				UNKNOWNENGINE_INLINE
				Core::PackedMessage packMessage ( const CameraLookAtActionMessage& msg ) override
				{
 					Core::PackedMessage result ( getMessageType(), sender_info );
					result.getProperties().set<Math::Vector3> ( "look_at_position", msg.look_at_position );
					return result;
				}

		};

		/**
		 * @brief Message unpacker for UpdateFrameMessage
		 */
		class CameraLookAtActionMessageUnpacker: public Core::MessageUnpacker<CameraLookAtActionMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				CameraLookAtActionMessage unpackMessage ( const Core::PackedMessage &msg ) throw ( Core::InvalidMessageFormatException ) override
				{
					CameraLookAtActionMessage result;
					result.look_at_position = msg.getProperties().get<Math::Vector3> ( "look_at_position" );
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
