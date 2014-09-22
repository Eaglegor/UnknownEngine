#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <Keys.h>
#include <KeycodeHash.h>
#include <ActionSlots/SimpleActionSlot.h>
#include <Spinlock.h>

namespace UnknownEngine
{
	namespace IO
	{

		class InputContextMapper;
		
		class KeyboardEventHandler
		{
		public:
			KeyboardEventHandler(InputContextMapper* context_mapper);
			
			void processEvent(const Key &key, const KeyState &new_state);
			
			void addActionSlotSubscription(const std::string& context_name, const std::string &action_slot_name, const Key& expected_key);
			void clearSubscriptions();
			
		private:
			typedef Utils::Spinlock LockPrimitive;
			
			std::vector<SimpleActionSlot*>* findSubscriptions(const Key &key);
			
			std::unordered_map< Key, std::vector< SimpleActionSlot* > > subscriptions;
			InputContextMapper* context_mapper;
			LockPrimitive lock_primitive;
		};
		
	}
}