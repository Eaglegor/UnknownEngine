#pragma once

/*
 * IMessageReceivePolicy.h
 *
 *  Created on: 19 июня 2014 г.
 *      Author: Eaglegor
 */

namespace UnknownEngine
{
	namespace Core
	{

		class PackedMessage;

		class IMessageReceivePolicy
		{
			public:
				virtual bool acceptMessage(const PackedMessage &msg) = 0;
				virtual ~IMessageReceivePolicy()
				{
				}

			protected:
				IMessageReceivePolicy()
				{
				}
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
