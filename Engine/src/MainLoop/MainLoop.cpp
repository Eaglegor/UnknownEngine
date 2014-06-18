/*
 * MainLoop.cpp
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <time.h>

#include <MainLoop/MainLoopEvent.h>
#include <MainLoop/MainLoop.h>

namespace UnknownEngine
{
	namespace Core
	{

		MainLoop::MainLoop ()
		{
			// TODO Auto-generated constructor stub

		}

		MainLoop::~MainLoop ()
		{
			// TODO Auto-generated destructor stub
		}

		void MainLoop::addBeforeFrameListener ( IMainLoopEventListener* listener )
		{
			this->beforeFrameObserver.addListener ( listener );
		}

		void MainLoop::addUpdateFrameListener ( IMainLoopEventListener* listener )
		{
			this->updateFrameObserver.addListener ( listener );
		}

		void MainLoop::addAfterFrameListener ( IMainLoopEventListener* listener )
		{
			this->afterFrameObserver.addListener ( listener );
		}

		void MainLoop::start ()
		{
			current_time = clock() / static_cast<float>(CLOCKS_PER_SEC);
			while ( true )
			{
				beforeFrameObserver.notify(MainLoopEvent(dt));

				updateFrameObserver.notify(MainLoopEvent(dt));
				updateTime();

				afterFrameObserver.notify(MainLoopEvent(dt));
			}
		}

		void MainLoop::updateTime ()
		{
			float temp_time = clock() / static_cast<float>(CLOCKS_PER_SEC);
			dt = temp_time - current_time;
			current_time = temp_time;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
