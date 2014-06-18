#pragma once
/*
 * MainLoopEventObserver.h
 *
 *  Created on: 17 ���� 2014 �.
 *      Author: gorbachenko
 */

#include <vector>

#include <MainLoop/IMainLoopEventListener.h>

namespace UnknownEngine
{
	namespace Core
	{

		class MainLoopEvent;

		class MainLoopEventObserver
		{
			public:
				MainLoopEventObserver ();
				virtual ~MainLoopEventObserver ();

				void addListener(IMainLoopEventListener* listener);
				void notify(const MainLoopEvent &event);

			private:
				std::vector<IMainLoopEventListener* > listeners;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
