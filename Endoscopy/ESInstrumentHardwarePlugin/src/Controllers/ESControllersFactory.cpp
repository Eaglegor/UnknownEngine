#include <Controllers/ESControllersFactory.h>
#include <Controllers/Joystick/ESJoystickController.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		IESController* ESControllersFactory::createController ( const char* name, ESControllerType type )
		{
			switch(type)
			{
				case ESControllerType::JOYSTICK:
				{
					return createJoystickController(name);
				}
			};
		}

		void ESControllersFactory::destroyController ( IESController* controller )
		{
			switch(controller->getType())
			{
				case ESControllerType::JOYSTICK:
				{
					destroyJoystickController(controller);
					return;
				}
			}
		}
		
		IESController* ESControllersFactory::createBestController(const char* name)
		{
			return createJoystickController(name);
		}
		
		IESController* ESControllersFactory::createJoystickController(const char* name)
		{
			return new ESJoystickController(name, ESJoystickControllerDesc());
		}
		
		void ESControllersFactory::destroyJoystickController ( IESController* controller )
		{
			delete controller;
		}
		
	}
}