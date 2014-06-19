#pragma once
/*
 * UpdateFrameMessage.h
 *
 *  Created on: 19 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <MessageSystem/MessagePacker.h>
#include <InlineSpecification.h>
#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Core
	{

		struct UpdateFrameMessage
		{
			float dt;
		};

		class UpdateFrameMessagePacker : public MessagePacker<UpdateFrameMessage>
		{
			public:
				UNKNOWNENGINE_INLINE
				UpdateFrameMessage unpackMessage(const Message &msg) throw(InvalidMessageFormat)
				{
					UpdateFrameMessage result;
					result.dt = msg.getProperties().get<float>("dt");
					return result;
				}

				UNKNOWNENGINE_INLINE
				Message packMessage(const UpdateFrameMessage& msg)
				{
					Message result( UNKNOWN_MESSAGE_TYPE );
					result.getProperties().set<float>("dt", dt);
					return result;
				}
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
