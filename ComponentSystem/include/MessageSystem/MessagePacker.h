#pragma once
/*
 * MessageParser.h
 *
 *  Created on: 19 ���� 2014 �.
 *      Author: gorbachenko
 */

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
				MessagePacker ();
				virtual ~MessagePacker ();

				virtual T unpackMessage(const Message &msg) throw(InvalidMessageFormat) = 0;
				virtual Message packMessage(const T& msg) = 0;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
