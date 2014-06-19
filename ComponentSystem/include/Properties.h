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
				T get ( std::string name ) const
				{
					return T ();
				}

				template<typename T>
				void set ( std::string name, const T &value )
				{
				}

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
