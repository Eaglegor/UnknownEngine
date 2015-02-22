#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <WindowHandle.h>
#include <ComponentInterfaces/GUI/WindowEventsListenerComponent.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class GUIWindowComponent : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getTypeName(){return "GUIWindowComponent";}
			
			virtual Graphics::NativeWindowHandleType getWindowHandle() = 0;
			virtual const char* getWindowTitle() = 0;
			
			virtual void addWindowEventsListener(WindowEventsListenerComponent* listener) = 0;
			virtual void removeWindowEventsListener(WindowEventsListenerComponent* listener) = 0;
			
		};
	}
}