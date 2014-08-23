#pragma once

#include <InlineSpecification.h>
#include <Vectors/Vector3.h>
#include <MessageSystem/MessagePacker.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		/**
		 * @brief Command for camera to look at some position
		 *
		 */
		struct CameraLookAtActionMessage
		{

				UNKNOWNENGINE_INLINE
				static const std::string getTypeName()
				{
					return "Graphics.CameraLookAtActionMessage";
				}

				Math::Vector3 look_at_position;
		};

		/**
		 * @brief Message packer for UpdateFrameMessage
		 */
		class CameraLookAtActionMessagePacker: public Core::MessagePacker<CameraLookAtActionMessage>
		{
			public:

				CameraLookAtActionMessagePacker(Core::MessageSystemParticipantId sender_info) :
						Core::MessagePacker<CameraLookAtActionMessage>(sender_info)
				{
				}

				UNKNOWNENGINE_INLINE
				Core::PackedMessage packMessage(const CameraLookAtActionMessage& msg) override
				{
					Core::PackedMessage result(Core::MessageDictionary::getSingleton()->getMessageTypeId(CameraLookAtActionMessage::getTypeName()), sender_info);
					result.getProperties().set<Math::Vector3>("look_at_position", msg.look_at_position);
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
				CameraLookAtActionMessage unpackMessage(const Core::PackedMessage &msg) throw (Core::InvalidMessageFormatException) override
				{
					CameraLookAtActionMessage result;
					result.look_at_position = msg.getProperties().get<Math::Vector3>("look_at_position");
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
