#pragma once
/*
 * UpdateFrameMessage.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: gorbachenko
 */

#include <MessageSystem/MessagePacker.h>
#include <InlineSpecification.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		struct UpdateFrameMessage
		{

				UNKNOWNENGINE_INLINE
				constexpr static const char* getTypeName()
				{
					return "Engine.MainLoop.UpdateFrame";
				}

				enum Stage
				{
					PREPROCESSING = 0, PROCESSING = 1, POSTPROCESSING = 2
				};

				Stage stage;
				float dt;
		};

		class UpdateFrameMessagePacker: public MessagePacker<UpdateFrameMessage>
		{
			public:

				UpdateFrameMessagePacker(SenderInfo sender_info) :
						MessagePacker<UpdateFrameMessage>(sender_info)
				{
				}

				UNKNOWNENGINE_INLINE
				PackedMessage packMessage(const UpdateFrameMessage& msg)
				{
					PackedMessage result(MessageDictionary::getSingleton()->getMessageTypeId(UpdateFrameMessage::getTypeName()), sender_info);
					result.getProperties().set<float>("dt", msg.dt);
					result.getProperties().set<int>("stage", msg.stage);
					return result;
				}

		};

		class UpdateFrameMessageUnpacker: public MessageUnpacker<UpdateFrameMessage>
		{
			public:

				UNKNOWNENGINE_INLINE
				UpdateFrameMessage unpackMessage(const PackedMessage &msg) throw (InvalidMessageFormatException)
				{
					UpdateFrameMessage result;
					result.dt = msg.getProperties().get<float>("dt");
					switch (msg.getProperties().get<int>("stage"))
					{
						case 0:
							result.stage = UpdateFrameMessage::PREPROCESSING;
							break;
						case 2:
							result.stage = UpdateFrameMessage::POSTPROCESSING;
							break;
						default:
							result.stage = UpdateFrameMessage::PROCESSING;
							break;
					}
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
