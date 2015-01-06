#include <stdafx.h>
#include <EventHandlers/JoystickEventHandler.h>
#include <InputContextMapper.h>
#include <mutex>

namespace UnknownEngine
{
	namespace IO
	{
		
		JoystickEventHandler::JoystickEventHandler ( InputContextMapper* context_mapper ):
		context_mapper(context_mapper)
		{
		}
		
		void JoystickEventHandler::setJoystickAxisValueMapping ( int lowest_value, int highest_value, float lowest_new_value, float highest_new_value )
		{
			range_mapper.reset(new Utils::ValueRangeMapper<Math::Scalar> (lowest_value, highest_value, lowest_new_value, highest_new_value));
		}

		void JoystickEventHandler::resetJoystickAxisValueMapping()
		{
			range_mapper.reset();
		}
		
		void JoystickEventHandler::clearSubscriptions()
		{
			std::lock_guard<LockPrimitive> guard(lock_primitive);
			joystick_button_subscriptions.clear();
			joystick_axis_subscriptions.clear();
		}
		
		std::vector< SimpleActionSlot* >* JoystickEventHandler::findButtonSubscriptions ( const uint8_t joystick_id, const uint8_t joystick_button )
		{
			auto iter = joystick_button_subscriptions.find(joystick_id);
			if(iter == joystick_button_subscriptions.end()) return nullptr;
			auto iter2 = iter->second.find(joystick_button);
			if(iter2 == iter->second.end()) return nullptr;
			return &iter2->second;
		}

		std::vector< RangeActionSlot* >* JoystickEventHandler::findAxisSubscriptions ( const uint8_t joystick_id, const uint8_t joystick_axis )
		{
			auto iter = joystick_axis_subscriptions.find(joystick_id);
			if(iter == joystick_axis_subscriptions.end()) return nullptr;
			auto iter2 = iter->second.find(joystick_axis);
			if(iter2 == iter->second.end()) return nullptr;
			return &iter2->second;
		}

		void JoystickEventHandler::addButtonActionSlotSubscription ( const std::string& context_name, const std::string& action_slot_name, const uint8_t joystick_id, const uint8_t joystick_button )
		{
			InputContext* context = context_mapper->findContext(context_name);
			if(context != nullptr)
			{
				SimpleActionSlot* action_slot = context->findSimpleActionSlot(action_slot_name);
				if(action_slot == nullptr) return;
				auto iter = joystick_button_subscriptions.find(joystick_id);
				if(iter == joystick_button_subscriptions.end())
				{
					iter = joystick_button_subscriptions.emplace(joystick_id, std::unordered_map<uint8_t, std::vector<SimpleActionSlot*> >()).first;
				}
				auto iter2 = iter->second.find(joystick_button);
				if(iter2 == iter->second.end()) 
				{
					iter2 = iter->second.emplace(joystick_button, std::vector<SimpleActionSlot*>()).first;
				}
				iter2->second.push_back(action_slot);
			}
		}

		void JoystickEventHandler::addAxisActionSlotSubscription ( const std::string& context_name, const std::string& action_slot_name, const uint8_t joystick_id, const uint8_t joystick_axis )
		{
			InputContext* context = context_mapper->findContext(context_name);
			if(context != nullptr)
			{
				RangeActionSlot* action_slot = context->findRangeActionSlot(action_slot_name);
				if(action_slot == nullptr) return;
				auto iter = joystick_axis_subscriptions.find(joystick_id);
				if(iter == joystick_axis_subscriptions.end())
				{
					iter = joystick_axis_subscriptions.emplace(joystick_id, std::unordered_map<uint8_t, std::vector<RangeActionSlot*> >()).first;
				}
				auto iter2 = iter->second.find(joystick_axis);
				if(iter2 == iter->second.end()) 
				{
					iter2 = iter->second.emplace(joystick_axis, std::vector<RangeActionSlot*>()).first;
				}
				iter2->second.push_back(action_slot);
			}
		}

		void JoystickEventHandler::processEvent (const uint8_t joystick_id, const uint8_t joystick_button, const JoystickButtonState& new_state )
		{
			std::lock_guard<LockPrimitive> guard(lock_primitive);
			std::vector<SimpleActionSlot*>* subscriptions = findButtonSubscriptions(joystick_id, joystick_button);
			if(subscriptions != nullptr)
			{
				for(SimpleActionSlot* action_slot : *subscriptions)
				{
					action_slot->onEvent( new_state == JoystickButtonState::PRESSED );
				}
			}
		}

		void JoystickEventHandler::processEvent ( const uint8_t joystick_id, const uint8_t joystick_axis, const int32_t new_value )
		{
			std::lock_guard<LockPrimitive> guard(lock_primitive);
			std::vector<RangeActionSlot*>* subscriptions = findAxisSubscriptions(joystick_id, joystick_axis);
			if(subscriptions != nullptr)
			{
				Math::Scalar event_value = range_mapper ? range_mapper->getMappedValue(new_value) : new_value;
				for(RangeActionSlot* action_slot : *subscriptions)
				{
					action_slot->onEvent( event_value );
				}
			}
		}
		
	}
}