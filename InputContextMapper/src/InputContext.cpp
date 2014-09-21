#include <InputContext.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		void InputContext::addAction ( const std::string& action_slot_name, std::function< void() > action )
		{
			auto iter = actions.find(action_slot_name);
			if(iter == actions.end()) return;
			iter->second->setAction(action);
		}

		void InputContext::addAction ( const std::string& action_slot_name, std::function< void(const Math::Scalar&) > action )
		{
			auto iter = actions.find(action_slot_name);
			if(iter == actions.end()) return;
			iter->second->setAction(action);
		}
		
		void InputContext::addActionSlot ( const std::string& action_slot_name, std::unique_ptr<ActionSlot> action_slot )
		{
			actions.emplace( action_slot_name, std::move(action_slot) );
		}

		void InputContext::processEvent ( const Key& key, const KeyState& new_state )
		{
			for(auto &iter : actions)
			{
				iter.second->processEvent(key, new_state);
			}
		}

		void InputContext::update()
		{
			for(auto &iter : actions)
			{
				iter.second->update();
			}
		}
		
	}
}