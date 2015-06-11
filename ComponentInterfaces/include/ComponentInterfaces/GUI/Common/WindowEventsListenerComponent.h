#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class WindowEventsListenerComponent: public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "WindowEventsListenerComponent";}
			
			virtual void onWindowResized(size_t new_width, size_t new_height) = 0;
			virtual void onWindowClosed() = 0;
			
		};
	}
}