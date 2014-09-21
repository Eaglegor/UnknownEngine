#pragma once

#include <Keys.h>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		class ActionCondition
		{
		public:
			virtual void update(const Key& key, const KeyState &state) = 0;
			virtual Math::Scalar getState() = 0;
			
			virtual void reset() = 0;
			
			virtual bool isTrue() = 0;
		};
		
	}
}