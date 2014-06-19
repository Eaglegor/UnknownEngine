#pragma once
/*
 * UpdateFrameMessage.h
 *
 *  Created on: 19 ���� 2014 �.
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

				enum Stage
				{
					PREPROCESSING, PROCESSING, POSTPROCESSING
				};

				Stage stage;
				float dt;
		};

		class UpdateFrameMessagePacker: public MessagePacker< UpdateFrameMessage >
		{
			public:

				UpdateFrameMessagePacker ( std::string sender_name )
						: MessagePacker< UpdateFrameMessage > ( sender_name )
				{
				}

				UNKNOWNENGINE_INLINE
				UpdateFrameMessage unpackMessage ( const Message &msg ) throw ( InvalidMessageFormat )
				{
					UpdateFrameMessage result;
					result.dt = msg.getProperties ().get< float > ( "dt" );
					result.stage = msg.getProperties ().get < UpdateFrameMessage::Stage > ( "stage" );
					return result;
				}

				UNKNOWNENGINE_INLINE
				Message packMessage ( const UpdateFrameMessage& msg )
				{
					Message result ( UNKNOWN_MESSAGE_TYPE, sender_name );
					result.getProperties ().set< float > ( "dt", msg.dt );
					result.getProperties ().set < UpdateFrameMessage::Stage > ( "stage", msg.stage );
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
