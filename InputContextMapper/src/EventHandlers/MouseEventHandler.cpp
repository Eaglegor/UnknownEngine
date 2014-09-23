#include <EventHandlers/MouseEventHandler.h>
#include <InputContextMapper.h>
#include <mutex>

namespace UnknownEngine
{
	namespace IO
	{
		
		MouseEventHandler::MouseEventHandler ( InputContextMapper* context_mapper ):
		context_mapper(context_mapper)
		{
		}
		
		void MouseEventHandler::clearSubscriptions()
		{
			std::lock_guard<LockPrimitive> guard(lock_primitive);
			mouse_button_subscriptions.clear();
			mouse_move_subscriptions.clear();
		}
		
		std::vector< SimpleActionSlot* >* MouseEventHandler::findSubscriptions ( const uint8_t mouse_button )
		{
			auto iter = mouse_button_subscriptions.find(mouse_button);
			if(iter == mouse_button_subscriptions.end()) return nullptr;
			return &iter->second;
		}

		std::vector< RangeActionSlot* >* MouseEventHandler::findSubscriptions ( const MouseAxis mouse_axis )
		{
			auto iter = mouse_move_subscriptions.find(mouse_axis);
			if(iter == mouse_move_subscriptions.end()) return nullptr;
			return &iter->second;
		}

		void MouseEventHandler::addActionSlotSubscription ( const std::string& context_name, const std::string& action_slot_name, const uint8_t mouse_button )
		{
			InputContext* context = context_mapper->findContext(context_name);
			if(context != nullptr)
			{
				SimpleActionSlot* action_slot = context->findSimpleActionSlot(action_slot_name);
				auto iter = mouse_button_subscriptions.find(mouse_button);
				if(iter == mouse_button_subscriptions.end())
				{
					iter = mouse_button_subscriptions.emplace(mouse_button, std::vector<SimpleActionSlot*>()).first;
				}
				iter->second.push_back(action_slot);
			}
		}

		void MouseEventHandler::addActionSlotSubscription ( const std::string& context_name, const std::string& action_slot_name, const MouseAxis mouse_axis )
		{
			InputContext* context = context_mapper->findContext(context_name);
			if(context != nullptr)
			{
				RangeActionSlot* action_slot = context->findRangeActionSlot(action_slot_name);
				auto iter = mouse_move_subscriptions.find(mouse_axis);
				if(iter == mouse_move_subscriptions.end())
				{
					iter = mouse_move_subscriptions.emplace(mouse_axis, std::vector<RangeActionSlot*>()).first;
				}
				iter->second.push_back(action_slot);
			}
		}

		void MouseEventHandler::processEvent ( const uint8_t mouse_button, const UnknownEngine::IO::MouseButtonState& new_state )
		{
			std::lock_guard<LockPrimitive> guard(lock_primitive);
			std::vector<SimpleActionSlot*>* subscriptions = findSubscriptions(mouse_button);
			if(subscriptions != nullptr)
			{
				for(SimpleActionSlot* action_slot : *subscriptions)
				{
					action_slot->onEvent( new_state == MouseButtonState::MOUSE_BUTTON_PRESSED );
				}
			}
		}

		void MouseEventHandler::processEvent ( const UnknownEngine::IO::MouseAxis mouse_axis, const int32_t delta_axis )
		{
			std::lock_guard<LockPrimitive> guard(lock_primitive);
			std::vector<RangeActionSlot*>* subscriptions = findSubscriptions(mouse_axis);
			if(subscriptions != nullptr)
			{
				for(RangeActionSlot* action_slot : *subscriptions)
				{
					action_slot->onEvent( delta_axis );
				}
			}
		}
		
	}
}