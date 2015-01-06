#pragma once

#include <vector>
#include <SDL_joystick.h>

namespace UnknownEngine
{
	namespace GUI
	{
		class SDLJoystickWrapper
		{
		public:
			SDLJoystickWrapper();
			~SDLJoystickWrapper();
			
		private:
			std::vector<SDL_Joystick*> joysticks;
		};
	}
}