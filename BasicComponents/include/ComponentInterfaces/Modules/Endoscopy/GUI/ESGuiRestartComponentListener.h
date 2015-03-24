#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESGuiRestartComponentListener : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "ESGuiRestartComponentListener";}

				virtual void onRestart() = 0;
		};
	}
}