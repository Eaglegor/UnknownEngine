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

		class Message;
		typedef std::exception InvalidMessageFormat;

		template <typename T>
		class MessagePacker
		{
			public:
				MessagePacker (std::string sender_name);
				virtual ~MessagePacker ();

				virtual T unpackMessage(const Message &msg) throw(InvalidMessageFormat) = 0;
				virtual Message packMessage(const T& msg) = 0;
			protected:
				std::string sender_name;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
