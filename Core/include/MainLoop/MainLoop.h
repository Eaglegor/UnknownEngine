#pragma once
/*
 * MainLoop.h
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <vector>

#include <MainLoop/MainLoopEventObserver.h>
#include <MainLoop/IMainLoopEventListener.h>

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

				void addBeforeFrameListener(IMainLoopEventListener* listener);
				void addUpdateFrameListener(IMainLoopEventListener* listener);
				void addAfterFrameListener(IMainLoopEventListener* listener);

			private:
				void updateTime();

				MainLoopEventObserver beforeFrameObserver;
				MainLoopEventObserver updateFrameObserver;
				MainLoopEventObserver afterFrameObserver;

				float current_time;
				float dt;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
