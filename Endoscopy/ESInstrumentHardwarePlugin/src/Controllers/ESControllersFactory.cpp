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
			return nullptr;
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
			ESJoystickControllerDesc desc;
			desc.update_frame_provider = Core::ComponentsManager::getSingleton()->findComponent("Engine.MainLoop");
			return new ESJoystickController(name, desc);
		}
		
		void ESControllersFactory::destroyJoystickController ( IESController* controller )
		{
			delete controller;
		}
		
	}
}