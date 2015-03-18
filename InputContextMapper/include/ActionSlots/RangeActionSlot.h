#pragma once

#include <functional>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		class InputContext;

		class RangeActionSlot
		{
		public:
			typedef std::function<void(Math::Scalar)> ActionType;

			RangeActionSlot(InputContext* context);
			~RangeActionSlot();
			
			void update();
			
			void setAction(ActionType action);
			void reset();
			
			void onEvent(Math::Scalar new_state);
			
			bool isActive();

		private:
			InputContext* context;
			ActionType action;
			Math::Scalar current_state;
			
		};
		
	}
}