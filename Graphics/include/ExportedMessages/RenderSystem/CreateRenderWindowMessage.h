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
#include <RenderTargets/RenderWindowDesc.h>

namespace UnknownEngine
{

	namespace Graphics
	{

		struct CreateRenderWindowMessage
		{
			static const std::string MSG_TYPE_NAME;

			RenderWindowDesc window_desc;
		};

		class CreateRenderWindowMessagePacker: public Core::MessagePacker< CreateRenderWindowMessage >
		{
			public:

				CreateRenderWindowMessagePacker ( std::string sender_name )
						: Core::MessagePacker< CreateRenderWindowMessage > ( sender_name )
				{
				}

				UNKNOWNENGINE_INLINE
				CreateRenderWindowMessage unpackMessage ( const Core::Message &msg ) throw ( Core::InvalidMessageFormat )
				{
					CreateRenderWindowMessage result;
					result.window_desc = msg.getProperties().get<RenderWindowDesc>("window_desc");
					return result;
				}

				UNKNOWNENGINE_INLINE
				Core::Message packMessage ( const CreateRenderWindowMessage& msg )
				{
					Core::Message result ( Core::MessageDictionary::getSingleton()->getMessageTypeId(CreateRenderWindowMessage::MSG_TYPE_NAME), sender_name );
					result.getProperties ().set< RenderWindowDesc > ( "window_desc", msg.window_desc );
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
