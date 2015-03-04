#pragma once
#include <ComponentSystem/IComponentInterface.h>
#include <Events/JoystickAxisEvent.h>
#include <Events/JoystickButtonEvent.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IJoystickEventsListener : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "IJoystickEventsListener";}
			
			virtual void onJoystickAxisEvent(const IO::JoystickAxisEvent &evt) = 0;
			virtual void onJoystickButtonEvent(const IO::JoystickButtonEvent &evt) = 0;
		};
	}
}