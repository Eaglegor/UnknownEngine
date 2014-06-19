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
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		struct UpdateFrameMessage
		{

				enum Stage
				{
					PREPROCESSING = 0, PROCESSING = 1, POSTPROCESSING = 2
				};

				static const std::string MSG_TYPE_NAME;

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
				UpdateFrameMessage unpackMessage ( const Message &msg ) throw ( InvalidMessageFormatException )
				{
					UpdateFrameMessage result;
					result.dt = msg.getProperties ().get< float > ( "dt" );
					switch(msg.getProperties ().get < int > ( "stage" )){
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

				UNKNOWNENGINE_INLINE
				Message packMessage ( const UpdateFrameMessage& msg )
				{
					Message result ( MessageDictionary::getSingleton()->getMessageTypeId(UpdateFrameMessage::MSG_TYPE_NAME), sender_name );
					result.getProperties ().set< float > ( "dt", msg.dt );
					result.getProperties ().set < int > ( "stage", msg.stage );
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
