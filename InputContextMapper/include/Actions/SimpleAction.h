#pragma once

#include <Actions/IAction.h>
#include <functional>

namespace UnknownEngine
{
	namespace IO
	{
		class SimpleAction : public IAction
		{
		public:
			typedef std::function<void()> CallbackType;
			
			virtual void onEventStarted() = 0;
			virtual void onEventEnded() = 0;
		};
	}
}