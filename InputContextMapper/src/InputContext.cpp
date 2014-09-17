#include <InputContext.h>
#include <Actions/ActionsFactory.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		InputContext::InputContext( bool enabled ):
		enabled(enabled)
		{
		}
		
		void InputContext::performActions()
		{
			for(auto& iter : keyboard_events)
			{
				iter.second.performAction();
			}
		}

		void InputContext::addSimpleActionPerformer ( const SimpleActionPerformerDescriptor& desc )
		{
			for(auto& iter : keyboard_events)
			{
				if(iter.second.getActionName() == desc.action_name)
				{
					iter.second.setAction( std::move( ActionsFactory::createSimpleAction(desc) ) );
				}
			}
		}
		
		InputContext::EventInterceptionStatus InputContext::processEvent ( Key& key, KeyState& state )
		{
			auto iter = keyboard_events.find(key);
			if(iter != keyboard_events.end())
			{
				bool intercepted = iter->second.processEvent(state);
				if(intercepted) return EventInterceptionStatus::INTERCEPTED;
			}
			return EventInterceptionStatus::NOT_INTERCEPTED;
		}

		bool InputContext::isEnabled() const
		{
			return enabled;
		}

		void InputContext::setEnabled ( bool new_enabled )
		{
			enabled = new_enabled;
		}

	}
}