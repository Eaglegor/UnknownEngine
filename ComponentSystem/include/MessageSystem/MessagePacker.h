#pragma once
/*
 * MessageParser.h
 *
 *  Created on: 19 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <string>

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

				MessagePacker ( std::string sender_name )
						: sender_name ( sender_name )
				{
				}

				virtual ~MessagePacker (){};

				virtual PackedMessage packMessage ( const T& msg ) = 0;
			protected:
				std::string sender_name;
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
