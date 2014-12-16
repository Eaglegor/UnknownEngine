#pragma once

#include <Controllers/IESController.h>
#include <Controllers/ESControllerType.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		class ESControllersFactory
		{
		public:
			IESController* createController(const char* name, ESControllerType type);
			IESController* createBestController(const char* name);
			
			void destroyController(IESController* controller);
			
		private:
			IESController* createJoystickController(const char* name);
			void destroyJoystickController(IESController* controller);
		};
	}
}