#pragma once
/*
 * IMainLoopEventListener.h
 *
 *  Created on: 17 ���� 2014 �.
 *      Author: gorbachenko
 */

namespace UnknownEngine
{

	namespace Core
	{

		class MainLoopEvent;

		class IMainLoopEventListener
		{
			public:
				virtual void onEvent ( const MainLoopEvent &event ) = 0;
				virtual ~IMainLoopEventListener(){}
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
