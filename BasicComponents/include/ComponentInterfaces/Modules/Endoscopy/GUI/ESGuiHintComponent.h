#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESGuiHintComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "ESGuiHintComponent";}
				
				virtual void setText(const char* text) = 0;
		};
	}
}