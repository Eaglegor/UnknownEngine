#pragma once

#include <Keys.h>
#include <Actions/SimpleAction.h>
#include <boost/optional.hpp>
#include <memory>

namespace UnknownEngine
{
	namespace IO
	{
		class KeyboardEventHandler
		{
		public:
			KeyboardEventHandler(const std::string &action_name, bool intercept_event);
			void setAction(std::unique_ptr<SimpleAction> action);
			bool processEvent(KeyState &new_state);
			void performAction();
			const std::string& getActionName();
			
		private:
			std::string action_name;
			bool intercept_event;
			std::unique_ptr<SimpleAction> action;
		};
	}
}