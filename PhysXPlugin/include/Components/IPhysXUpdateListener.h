#pragma once

namespace UnknownEngine
{
	namespace Physics
	{
		class IPhysXUpdateListener
		{
		public:
			virtual void update() = 0;
		};
	}
}