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
#include <MessageSystem/MessageDictionary.h>

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
					Message result ( MessageDictionary::getSingleton()->getMessageTypeId(UpdateFrameMessage::MSG_TYPE_NAME), sender_name );
					result.getProperties ().set< float > ( "dt", msg.dt );
					result.getProperties ().set < UpdateFrameMessage::Stage > ( "stage", msg.stage );
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
