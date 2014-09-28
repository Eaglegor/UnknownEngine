#include <EventHandlers/KeyboardEventHandler.h>
#include <InputContextMapper.h>
#include <mutex>

namespace UnknownEngine
{
	namespace IO
	{
		
		KeyboardEventHandler::KeyboardEventHandler ( InputContextMapper* context_mapper ):
		context_mapper(context_mapper)
		{
		}
		
		void KeyboardEventHandler::addActionSlotSubscription ( const std::string& context_name, const std::string& action_slot_name, const Key& expected_key )
		{
			InputContext* context = context_mapper->findContext(context_name);
			if(context != nullptr)
			{
				SimpleActionSlot* action_slot = context->findSimpleActionSlot(action_slot_name);
				if(action_slot == nullptr) return;
				
				auto iter = subscriptions.find(expected_key);
				if(iter == subscriptions.end())
				{
					iter = subscriptions.emplace(expected_key, std::vector<SimpleActionSlot*>()).first;
				}
				iter->second.push_back(action_slot);
			}
		}

		void KeyboardEventHandler::clearSubscriptions()
		{
			std::lock_guard<LockPrimitive> guard(lock_primitive);
			subscriptions.clear();
		}
		
		void KeyboardEventHandler::processEvent ( const Key& key, const KeyState& new_state )
		{
			std::lock_guard<LockPrimitive> guard(lock_primitive);
			std::vector<SimpleActionSlot*>* subscriptions = findSubscriptions(key);
			if(subscriptions != nullptr)
			{
				for(SimpleActionSlot* action_slot : *subscriptions)
				{
					action_slot->onEvent( new_state == KeyState::KEY_PRESSED );
				}
			}
		}
		
		std::vector< SimpleActionSlot *>* KeyboardEventHandler::findSubscriptions ( const Key& key )
		{
			auto iter = subscriptions.find(key);
			if(iter == subscriptions.end()) return nullptr;
			return &iter->second;
		}

	}
}