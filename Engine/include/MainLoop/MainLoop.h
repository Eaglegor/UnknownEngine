#pragma once
/*
 * MainLoop.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: gorbachenko
 */

#include <vector>

namespace UnknownEngine
{
	namespace Core
	{

		class MainLoop
		{
			public:
				MainLoop ();
				virtual ~MainLoop ();

				void start();

			private:
				void updateTime();

				float current_time;
				float dt;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
