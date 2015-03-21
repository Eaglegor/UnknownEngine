#include <stdafx.h>
#include <InputContext.h>

namespace UnknownEngine
{
	namespace IO
	{

		InputContext::InputContext(const char* name) :
		name(name),
		is_active(false)
		{}

		RangeActionSlot* InputContext::createRangeActionSlot( const std::string& action_slot_name )
		{
			return &(range_actions.emplace(action_slot_name, RangeActionSlot(this)).first->second);
		}
		
		SimpleActionSlot* InputContext::createSimpleActionSlot( const std::string& action_slot_name, const UnknownEngine::IO::SimpleActionSlot::ConditionType& condition_type )
		{
			return &(simple_actions.emplace(std::string(action_slot_name), SimpleActionSlot(this, condition_type)).first->second);
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

		bool InputContext::isActive()
		{
			return is_active;
		}

		void InputContext::setActive(bool value)
		{
			this->is_active = value;
		}

		const char* InputContext::getName()
		{
			return name.c_str();
		}
		
	}
}