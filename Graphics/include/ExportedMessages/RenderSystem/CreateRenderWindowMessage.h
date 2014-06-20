#pragma once
/*
 * UpdateFrameMessage.h
 *
 *  Created on: 19 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <boost/any.hpp>

#include <InlineSpecification.h>

#include <MessageSystem/MessagePacker.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/SenderInfo.h>

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

				CreateRenderWindowMessagePacker ( Core::SenderInfo sender_info )
						: Core::MessagePacker< CreateRenderWindowMessage > ( sender_info )
				{
				}

				UNKNOWNENGINE_INLINE
				Core::PackedMessage packMessage ( const CreateRenderWindowMessage& msg )
				{
					Core::PackedMessage result ( Core::MessageDictionary::getSingleton()->getMessageTypeId(CreateRenderWindowMessage::MSG_TYPE_NAME), sender_info );
					result.getProperties ().set< boost::any > ( "window_desc", boost::any(msg.window_desc) );
					return result;
				}

		};

		class CreateRenderWindowMessageUnpacker: public Core::MessageUnpacker< CreateRenderWindowMessage >
		{
			public:

				UNKNOWNENGINE_INLINE
				CreateRenderWindowMessage unpackMessage ( const Core::PackedMessage &msg ) throw ( Core::InvalidMessageFormatException )
				{
					CreateRenderWindowMessage result;
					boost::any any_desc = msg.getProperties().get< boost::any >("window_desc");
					result.window_desc = boost::any_cast<RenderWindowDesc> (any_desc);
					return result;
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
