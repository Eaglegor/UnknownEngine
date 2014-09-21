#include <ActionSlot.h>
#include <boost/variant/static_visitor.hpp>

#include <iostream>

namespace UnknownEngine
{
	namespace IO
	{

		class ActionSlot::Visitor : public boost::static_visitor<void>
		{
		public:
			
			Visitor():
			current_state(0)
			{
				
			}
			
			void updateState(Math::Scalar new_state)
			{
				current_state = new_state;
			}
			
			void operator()(const std::nullptr_t &val)
			{
				
			}
			
			void operator()(const std::function<void()> &action)
			{
				action();
			}
			
			void operator()(const std::function<void(const Math::Scalar&)> &action)
			{
				action(current_state);
			}
			
		private:
			Math::Scalar current_state;
		};
		
		ActionSlot::ActionSlot():
		visitor(new Visitor())
		{

		}

		ActionSlot::~ActionSlot()
		{

		}
		
		void ActionSlot::setAction ( std::function< void() > action )
		{
			this->action = action;
		}

		void ActionSlot::setAction ( std::function< void(const Math::Scalar&) > action )
		{
			this->action = action;
		}
		
		void ActionSlot::processEvent ( const Key& key, const KeyState& new_state )
		{
			if(condition) 
			{
				condition->update(key, new_state);
			}
		}

		void ActionSlot::setCondition ( std::unique_ptr< ActionCondition >&& condition )
		{
			this->condition = std::move(condition);
		}

		void ActionSlot::update()
		{
			if(condition && condition->isTrue())
			{
				visitor->updateState(condition->getState());
				action.apply_visitor(*visitor);
				condition->reset();
			}
		}

		
	}
}