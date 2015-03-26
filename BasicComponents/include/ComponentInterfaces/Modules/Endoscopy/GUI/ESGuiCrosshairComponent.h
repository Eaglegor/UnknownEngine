#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
                class ESGuiCrosshairComponent : public Core::IComponentInterface
		{
			public:
                                constexpr static const char* getType(){return "ESGuiCrosshairComponent";}
				
                                virtual void setAimed(bool value) = 0;
		};
	}
}
