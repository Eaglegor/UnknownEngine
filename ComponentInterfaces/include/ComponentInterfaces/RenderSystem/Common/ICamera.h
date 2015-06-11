#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ICamera : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType()
				{
					return "ICamera";
				}
		};
	}
}
