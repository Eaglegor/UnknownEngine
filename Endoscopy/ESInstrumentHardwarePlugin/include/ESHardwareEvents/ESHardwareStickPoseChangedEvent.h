#pragma once
#include <Scalar.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		struct ESHardwareStickPoseChangedEvent
		{
			Math::Scalar x;
			Math::Scalar y;
			Math::Scalar z;
			Math::Scalar d;
		};
	}
}