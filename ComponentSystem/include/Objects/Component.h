#pragma once
/*
 * Component.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
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
