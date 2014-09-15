#pragma once

namespace UnknownEngine
{
	namespace IO
	{
		class IAction
		{
		public:
			virtual void perform() = 0;
			virtual void reset() = 0;
		};
	}
}