#pragma once

#include <Actions/IAction.h>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace IO
	{
		class RangedAction : public IAction
		{
		public:
			virtual void onEvent(Math::Scalar ranged_value) = 0;
		};
	}
}