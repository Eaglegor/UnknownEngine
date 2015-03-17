#pragma once
#include <ComponentSystem/IComponentInterface.h>
#include <Events/MouseButtonEvent.h>
#include <Events/MouseMovedEvent.h>
#include <Events/MouseWheelEvent.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IMouseEventsListener : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "IMouseEventsListener";}
			
			virtual void onMouseButtonEvent(const IO::MouseButtonEvent &evt) = 0;
			virtual void onMouseMoveEvent(const IO::MouseMovedEvent &evt) = 0;
			virtual void onMouseWheelEvent(const IO::MouseWheelEvent &evt) = 0;
		};
	}
}