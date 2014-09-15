#pragma once

#include <Actions/IAction.h>

namespace UnknownEngine
{
	namespace IO
	{
		class SimpleAction : public IAction
		{
		public:
			virtual void onEventStarted() = 0;
			virtual void onEventEnded() = 0;
		};
	}
}