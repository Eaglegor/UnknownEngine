#pragma once

#include <Keys.h>
#include <Scalar.h>
#include <functional>
#include <unordered_map>
#include <ActionSlot.h>

namespace UnknownEngine
{
	namespace IO
	{
		class InputContext
		{
		public:
			void processEvent(const Key &key, const KeyState &new_state);
			void addAction(const std::string &action_slot_name, std::function<void()> action);
			void addAction(const std::string &action_slot_name, std::function<void(const Math::Scalar&)> action);
			
			void addActionSlot(const std::string &action_slot_name, std::unique_ptr<ActionSlot> action_slot);
			
			void update();
			
		private:
			
			std::unordered_map<std::string, std::unique_ptr<ActionSlot> > actions;
			
		};
	}
}