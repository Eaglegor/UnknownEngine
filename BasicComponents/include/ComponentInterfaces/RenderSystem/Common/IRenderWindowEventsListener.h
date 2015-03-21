#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IRenderWindowEventsListener : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "IRenderWindowEventsListener";}
			
			virtual void onRenderFrame() = 0;
		};
	}
}