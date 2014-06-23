#pragma once
/*
 * Component.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>

namespace UnknownEngine
{
	namespace Core
	{

		typedef std::string ComponentType;

		class Component
		{
			public:
				Component ();
				virtual ~Component ();
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
