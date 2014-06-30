#pragma once
/*
 * UpdateFrameMessage.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: gorbachenko
 */

#include <InlineSpecification.h>

#include <MessageSystem/MessagePacker.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>

#include <RenderTargets/RenderWindowDesc.h>

namespace UnknownEngine
{

	namespace Core
	{
		class MessageSystemParticipantId;
	}

	namespace Graphics
	{

		struct CreateRenderWindowMessage
		{
				UNKNOWNENGINE_INLINE
				constexpr static const char* getTypeName()
				{
					return "Graphics.RenderSystem.CreateRenderWindow";
				}

				RenderWindowDesc window_desc;
		};

		class CreateRenderWindowMessagePacker: public Core::MessagePacker<CreateRenderWindowMessage>
		{
			public:

				CreateRenderWindowMessagePacker(const Core::MessageSystemParticipantId &sender_info) :
						Core::MessagePacker<CreateRenderWindowMessage>(sender_info)
				{
				}

				UNKNOWNENGINE_INLINE
				Core::PackedMessage packMessage(const CreateRenderWindowMessage& msg) override
				{
					Core::PackedMessage result(Core::MessageDictionary::getSingleton()->getMessageTypeId(CreateRenderWindowMessage::getTypeName()),
							sender_info);
					result.getProperties().set<RenderWindowDesc>("window_desc", msg.window_desc);
					return result;
				}

		};

		class CreateRenderWindowMessageUnpacker: public Core::MessageUnpacker<CreateRenderWindowMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				CreateRenderWindowMessage unpackMessage(const Core::PackedMessage &msg) throw (Core::InvalidMessageFormatException) override
				{
					CreateRenderWindowMessage result;
					result.window_desc = msg.getProperties().get<RenderWindowDesc>("window_desc");
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
