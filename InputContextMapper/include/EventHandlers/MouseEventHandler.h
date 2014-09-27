#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <MouseButtonState.h>
#include <ActionSlots/SimpleActionSlot.h>
#include <ActionSlots/RangeActionSlot.h>
#include <Spinlock.h>
#include <MouseAxis.h>

namespace UnknownEngine
{
	namespace IO
	{

		class InputContextMapper;
		
		
		
		class MouseEventHandler
		{
		public:
			MouseEventHandler(InputContextMapper* context_mapper);
			
			void processEvent(const uint8_t mouse_button, const MouseButtonState &new_state);
			void processEvent(const MouseAxis mouse_axis, const int32_t delta_axis);
			
			void addActionSlotSubscription(const std::string& context_name, const std::string &action_slot_name, const uint8_t mouse_button);
			void addActionSlotSubscription(const std::string& context_name, const std::string &action_slot_name, const MouseAxis mouse_axis);
			void clearSubscriptions();
			
		private:
			typedef Utils::Spinlock LockPrimitive;
			
			std::vector<SimpleActionSlot*>* findSubscriptions(const uint8_t mouse_button);
			std::vector<RangeActionSlot*>* findSubscriptions(const MouseAxis mouse_axis);
			
			std::unordered_map< uint8_t, std::vector< SimpleActionSlot* > > mouse_button_subscriptions;
			std::unordered_map< MouseAxis, std::vector< RangeActionSlot* > > mouse_move_subscriptions;
			InputContextMapper* context_mapper;
			LockPrimitive lock_primitive;
		};
		
	}
}