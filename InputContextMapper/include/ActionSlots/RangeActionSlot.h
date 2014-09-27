#pragma once

#include <functional>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		class RangeActionSlot
		{
		public:
			typedef std::function<void(Math::Scalar)> ActionType;

			RangeActionSlot();
			~RangeActionSlot();
			
			void update();
			
			void setAction(ActionType action);
			
			void onEvent(Math::Scalar new_state);
			
		private:
			ActionType action;
			Math::Scalar current_state;
			
		};
		
	}
}