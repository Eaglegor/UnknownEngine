/*
 * MainLoopEventObserver.cpp
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <MainLoop/IMainLoopEventListener.h>
#include <MainLoop/MainLoopEventObserver.h>

namespace UnknownEngine
{
	namespace Core
	{

		MainLoopEventObserver::MainLoopEventObserver ()
		{
			// TODO Auto-generated constructor stub

		}

		MainLoopEventObserver::~MainLoopEventObserver ()
		{
			// TODO Auto-generated destructor stub
		}

		void MainLoopEventObserver::addListener ( IMainLoopEventListener* listener )
		{
			this->listeners.push_back(listener);
		}

		void MainLoopEventObserver::notify (const MainLoopEvent &event)
		{
			for(IMainLoopEventListener* listener : listeners)
			{
				listener->onEvent(event);
			}
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
