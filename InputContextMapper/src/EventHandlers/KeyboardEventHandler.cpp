#include <EventHandlers/KeyboardEventHandler.h>

namespace UnknownEngine
{
	namespace IO
	{
		KeyboardEventHandler::KeyboardEventHandler( const std::string& action_name, bool intercept_event ):
		action_name(action_name),
		intercept_event(intercept_event)
		{
		}

		bool KeyboardEventHandler::processEvent(KeyState &new_state)
		{
			if(!action) return true;
			switch(new_state)
			{
				case KeyState::KEY_PRESSED:
				{
					action->onEventStarted();
					break;
				}
				case KeyState::KEY_UNPRESSED:
				{
					action->onEventEnded();
					break;
				}
			}
			return intercept_event;
		}

		void KeyboardEventHandler::setAction ( std::unique_ptr<SimpleAction> action )
		{
			this->action = std::move(action);
		}
		
		const std::string& KeyboardEventHandler::getActionName()
		{
			return action_name;
		}
		
		void KeyboardEventHandler::performAction()
		{
			if(action) action->perform();
		}
		
	}
}