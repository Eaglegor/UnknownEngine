#pragma once

#include <unordered_map>
#include <ActionSlots/SimpleActionSlot.h>
#include <ActionSlots/RangeActionSlot.h>

namespace UnknownEngine
{
	namespace IO
	{
		class InputContext
		{
		public:
			RangeActionSlot* createRangeActionSlot(const std::string &action_slot_name);
			SimpleActionSlot* createSimpleActionSlot(const std::string &action_slot_name, const SimpleActionSlot::ConditionType &condition_type);

			SimpleActionSlot* findSimpleActionSlot(const std::string &action_slot_name);
			RangeActionSlot* findRangeActionSlot(const std::string &action_slot_name);
			
			void update();
			
		private:
			
			std::unordered_map<std::string, SimpleActionSlot> simple_actions;
			std::unordered_map<std::string, RangeActionSlot> range_actions;
			
			
		};
	}
}