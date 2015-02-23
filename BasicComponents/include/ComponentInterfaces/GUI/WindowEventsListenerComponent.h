#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class WindowEventsListenerComponent: public Core::IComponentInterface
		{
		public:
			constexpr static const char* getTypeName(){return "GUIWindowEventsListener";}
			
			virtual void onWindowResized(size_t new_width, size_t new_height) = 0;
			virtual void onWindowClosed() = 0;
			
		};
	}
}