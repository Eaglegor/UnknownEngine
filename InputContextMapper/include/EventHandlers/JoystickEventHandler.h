#pragma once

#include <JoystickButtonState.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <ActionSlots/SimpleActionSlot.h>
#include <ActionSlots/RangeActionSlot.h>
#include <Spinlock.h>
#include <MouseAxis.h>
#include <ValueRangeMapper.h>

namespace UnknownEngine
{
	namespace IO
	{
		class InputContextMapper;
		
		class JoystickEventHandler
		{
		public:
			JoystickEventHandler(InputContextMapper* context_mapper);
			
			void setJoystickAxisValueMapping(int lowest_value, int highest_value, float lowest_new_value, float highest_new_value);
			void resetJoystickAxisValueMapping();
			
			void processEvent(const uint8_t joystick_id, const uint8_t joystick_button, const JoystickButtonState &new_state);
			void processEvent(const uint8_t joystick_id, const uint8_t joystick_axis, const int32_t new_value);
			
			void addButtonActionSlotSubscription(const std::string& context_name, const std::string &action_slot_name, const uint8_t joystick_id, const uint8_t mouse_button);
			void addAxisActionSlotSubscription(const std::string& context_name, const std::string &action_slot_name, const uint8_t joystick_id, const uint8_t mouse_axis);
			void clearSubscriptions();
			
		private:
			typedef Utils::Spinlock LockPrimitive;
			
			std::vector<SimpleActionSlot*>* findButtonSubscriptions(const uint8_t joystick_id, const uint8_t joystick_button);
			std::vector<RangeActionSlot*>* findAxisSubscriptions(const uint8_t joystick_id, const uint8_t joystick_axis);
			
			typedef std::unordered_map< uint8_t, std::vector< SimpleActionSlot* > > JoystickButtonSubscriptions;
			typedef std::unordered_map< uint8_t, std::vector< RangeActionSlot* > > JoystickAxisSubscriptions;
			
			std::unordered_map<uint8_t, JoystickButtonSubscriptions> joystick_button_subscriptions;
			std::unordered_map<uint8_t, JoystickAxisSubscriptions> joystick_axis_subscriptions;
			
			//std::unordered_map< uint8_t, std::vector< SimpleActionSlot* > > joystick_button_subscriptions;
			//std::unordered_map< uint8_t, std::vector< RangeActionSlot* > > joystick_axis_subscriptions;
			
			InputContextMapper* context_mapper;
			LockPrimitive lock_primitive;
			
			std::unique_ptr<Utils::ValueRangeMapper<Math::Scalar> > range_mapper;
		};
	}
}