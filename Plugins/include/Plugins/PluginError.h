#pragma once

/*
 * PluginError.h
 *
 *  Created on: 17 ���� 2014 �.
 *      Author: Eaglegor
 */

#include <string>

namespace UnknownEngine
{
	namespace Core
	{
		class PluginError: public std::exception
		{
			public:
				PluginError(std::string message) :
						message(message)
				{
				}

				virtual const char* what() const throw() override{
					return message.c_str();
				}

			private:
				std::string message;

		};
	}
}
