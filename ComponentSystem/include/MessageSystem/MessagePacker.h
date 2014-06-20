#pragma once
/*
 * MessageParser.h
 *
 *  Created on: 19 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <string>
#include <MessageSystem/SenderInfo.h>

namespace UnknownEngine
{
	namespace Core
	{

		typedef std::exception InvalidMessageFormatException;
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
