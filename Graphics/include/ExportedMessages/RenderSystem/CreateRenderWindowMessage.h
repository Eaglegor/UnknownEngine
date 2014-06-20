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
#include <boost/any.hpp>

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
				CreateRenderWindowMessage unpackMessage ( const Core::PackedMessage &msg ) throw ( Core::InvalidMessageFormatException )
				{
					CreateRenderWindowMessage result;
					result.window_desc = boost::any_cast<RenderWindowDesc> (msg.getProperties().get< boost::any >("window_desc"));
					return result;
				}

				UNKNOWNENGINE_INLINE
				Core::PackedMessage packMessage ( const CreateRenderWindowMessage& msg )
				{
					Core::PackedMessage result ( Core::MessageDictionary::getSingleton()->getMessageTypeId(CreateRenderWindowMessage::MSG_TYPE_NAME), sender_name );
					result.getProperties ().set< boost::any > ( "window_desc", msg.window_desc );
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
