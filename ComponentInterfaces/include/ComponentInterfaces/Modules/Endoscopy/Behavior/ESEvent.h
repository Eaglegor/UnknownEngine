#pragma once

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		struct ESEvent
		{
			enum class Type
			{
				UNKNOWN,
				RESTART,
				INSTRUMENT_CHANGED,
				OBJECT_CATCHED
			};
			
			virtual Type getType() = 0;
		};
	}
}