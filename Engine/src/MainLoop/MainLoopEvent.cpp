/*
 * MainLoopEvent.cpp
 *
 *  Created on: 17 ���� 2014 �.
 *      Author: gorbachenko
 */

#include <MainLoop/MainLoopEvent.h>

namespace UnknownEngine
{
	namespace Core
	{

		MainLoopEvent::MainLoopEvent (float dt)
		{
			this->dt = dt;
		}

		MainLoopEvent::~MainLoopEvent ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
