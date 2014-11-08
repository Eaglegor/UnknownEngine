#include <stdafx.h>
#include <InputContext.h>

namespace UnknownEngine
{
	namespace IO
	{

		RangeActionSlot* InputContext::createRangeActionSlot( const std::string& action_slot_name )
		{
			return &(range_actions.emplace(action_slot_name, RangeActionSlot()).first->second);
		}
		
		SimpleActionSlot* InputContext::createSimpleActionSlot( const std::string& action_slot_name, const UnknownEngine::IO::SimpleActionSlot::ConditionType& condition_type )
		{
			return &(simple_actions.emplace(std::string(action_slot_name), SimpleActionSlot(condition_type)).first->second);
		}

		SimpleActionSlot* InputContext::findSimpleActionSlot(const std::string &action_slot_name)
		{
			auto iter = simple_actions.find(action_slot_name);
			if(iter == simple_actions.end()) return nullptr;
			return &iter->second;
		}
		
		RangeActionSlot* InputContext::findRangeActionSlot(const std::string &action_slot_name)
		{
			auto iter = range_actions.find(action_slot_name);
			if(iter == range_actions.end()) return nullptr;
			return &iter->second;
		}
		
		void InputContext::update()
		{
			for(auto &iter : simple_actions)
			{
				iter.second.update();
			}
			for(auto &iter : range_actions)
			{
				iter.second.update();
			}
		}
		
	}
}