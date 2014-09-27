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
			virtual void update(bool event_started) = 0;
			virtual bool isTrue() = 0;
		};
		
	}
}