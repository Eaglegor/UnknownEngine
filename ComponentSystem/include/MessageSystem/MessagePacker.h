#pragma once
/*
 * MessageParser.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>
#include <MessageSystem/SenderInfo.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		class InvalidMessageFormatException : public Exception{};
		class PackedMessage;

		template <typename T>
		class MessagePacker
		{
			public:

				MessagePacker ( SenderInfo sender_info )
						: sender_info ( sender_info )
				{
				}

				virtual ~MessagePacker (){};

				virtual PackedMessage packMessage ( const T& msg ) = 0;
			protected:
				SenderInfo sender_info;
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
