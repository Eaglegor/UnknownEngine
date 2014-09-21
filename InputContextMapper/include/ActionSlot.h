#pragma once

#include <functional>
#include <Scalar.h>
#include <Keys.h>
#include <ActionCondition.h>
#include <boost/variant.hpp>

namespace UnknownEngine
{
	namespace IO
	{
		class ActionSlot
		{
		public:
			ActionSlot();
			~ActionSlot();
			
			void update();
			void setAction(std::function<void()> action);
			void setAction(std::function<void(const Math::Scalar&)> action);
			
			void processEvent(const Key& key, const KeyState &new_state);
			
			void setCondition(std::unique_ptr<ActionCondition> &&condition);
			
		private:
			class Visitor;
			
			boost::variant< std::nullptr_t, std::function<void()>, std::function<void(const Math::Scalar&)> > action;
			std::unique_ptr<ActionCondition> condition;
			std::unique_ptr<Visitor> visitor;
		};
	}
}