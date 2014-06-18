#pragma once
/*
 * Properties.h
 *
 *  Created on: 18 ���� 2014 �.
 *      Author: gorbachenko
 */

#include <string>

namespace UnknownEngine
{
	namespace Core
	{

		class Properties
		{
			public:
				Properties ();
				virtual ~Properties ();

				template<typename T>
				T get ( std::string name )
				{
					return T();
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
