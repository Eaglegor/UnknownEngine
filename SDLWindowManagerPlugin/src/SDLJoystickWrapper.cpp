#include <SDLJoystickWrapper.h>

namespace UnknownEngine
{
	namespace GUI
	{
		SDLJoystickWrapper::SDLJoystickWrapper()
		{
			size_t joysticks_count = SDL_NumJoysticks();
			joysticks.reserve(joysticks_count);
			for(size_t i = 0; i < joysticks_count; ++i)
			{
				SDL_Joystick* joystick = SDL_JoystickOpen(i);
				joysticks.push_back(joystick);
			}
		}

		SDLJoystickWrapper::~SDLJoystickWrapper()
		{
			for(SDL_Joystick* joystick : joysticks)
			{
				if(joystick) SDL_JoystickClose(joystick);
			}
		}
	}
}