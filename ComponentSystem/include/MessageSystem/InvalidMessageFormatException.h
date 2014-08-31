#pragma once

#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{
		/// Is thrown if the packed message doesn't contain required fields or has values with wrong semantics (e.g. limit value exceeded)
		UNKNOWNENGINE_SIMPLE_EXCEPTION ( InvalidMessageFormatException );
	}
}

