#pragma once
/*
 * MessageParser.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>

#include <Exception.h>
#include <MessageSystem/MessageSystemParticipantId.h>

namespace UnknownEngine
{
	namespace Core
	{

		UNKNOWNENGINE_SIMPLE_EXCEPTION(InvalidMessageFormatException);

		class PackedMessage;

		template <typename T>
		class MessagePacker
		{
			public:

				MessagePacker ( const MessageSystemParticipantId &sender_info )
						: sender_info ( sender_info )
				{
				}

				virtual ~MessagePacker (){};

				virtual PackedMessage packMessage ( const T& msg ) = 0;
			protected:
				MessageSystemParticipantId sender_info;
		};

		template <typename T>
		class MessageUnpacker
		{
			public:

				MessageUnpacker ( )
				{
				}

				virtual ~MessageUnpacker (){};

				virtual T unpackMessage ( const PackedMessage &msg ) throw ( InvalidMessageFormatException ) = 0;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
