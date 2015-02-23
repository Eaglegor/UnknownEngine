#pragma once
#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{

		class IJoystickEventsListener;
		class IJoystickHandler : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getTypeName(){return "IJoystickHandler";}
			
			virtual void addJoystickEventsListener(IJoystickEventsListener* listener) = 0;
			virtual void removeJoystickEventsListener(IJoystickEventsListener* listener) = 0;
		};
	}
}