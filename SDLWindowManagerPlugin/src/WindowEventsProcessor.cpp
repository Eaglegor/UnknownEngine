#include <stdafx.h>
#include <WindowEventsProcessor.h>
#include <SDLWindowManager.h>
#include <ComponentInterfaces/GUI/Common/WindowEventsListenerComponent.h>

#include <Events/JoystickAxisEvent.h>
#include <Events/JoystickButtonEvent.h>
#include <Events/KeyboardEvent.h>
#include <Events/MouseButtonEvent.h>
#include <Events/MouseMovedEvent.h>
#include <Events/MouseWheelEvent.h>

#include <ComponentInterfaces/Input/Common/IJoystickEventsListener.h>
#include <ComponentInterfaces/Input/Common/IKeyboardEventsListener.h>
#include <ComponentInterfaces/Input/Common/IMouseEventsListener.h>

#include <SDL.h>

namespace UnknownEngine
{
	namespace GUI
	{
		WindowEventsProcessor::WindowEventsProcessor ( const std::string& name, SDLWindowManager* window_manager)
		{
		}
		
		void WindowEventsProcessor::processEvents()
		{
			SDL_Event event;

			while( SDL_PollEvent(&event) )
			{
				switch(event.type)
				{
					case SDL_KEYDOWN:
					case SDL_KEYUP:
					{
						if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_F3)
						{
							if(SDL_GetRelativeMouseMode() == SDL_TRUE)
							{
								SDL_SetRelativeMouseMode(SDL_FALSE);
							}
							else
							{
								SDL_SetRelativeMouseMode(SDL_TRUE);
							}
						}
						
						IO::KeyboardEvent evt;
						
						evt.key = keys_converter.getUnknownEngineKey(event.key.keysym.sym);
						evt.new_state = (event.type == SDL_KEYDOWN ? IO::KeyState::KEY_PRESSED : IO::KeyState::KEY_UNPRESSED);
						evt.character = event.key.keysym.sym;
						
						for(ComponentInterfaces::IKeyboardEventsListener* listener : keyboard_events_listeners)
						{
							listener->onKeyboardEvent(evt);
						}
						
						break;
					}
					case SDL_MOUSEBUTTONDOWN:
					case SDL_MOUSEBUTTONUP:
					{

						IO::MouseButtonEvent evt;

						evt.mouse_id = event.button.which;

						evt.new_state = (event.type == SDL_MOUSEBUTTONDOWN ? IO::MouseButtonState::MOUSE_BUTTON_PRESSED : IO::MouseButtonState::MOUSE_BUTTON_UNPRESSED);

						switch(event.button.button)
						{
							case SDL_BUTTON_LEFT:
							{
								evt.button_id = 0;
								break;
							}
							case SDL_BUTTON_RIGHT:
							{
								evt.button_id = 1;
								break;
							}
							case SDL_BUTTON_MIDDLE:
							{
								evt.button_id = 2;
								break;
							}
							case SDL_BUTTON_X1:
							{
								evt.button_id = 3;
								break;
							}
							case SDL_BUTTON_X2:
							{
								evt.button_id = 4;
								break;
							}
						}

						for(ComponentInterfaces::IMouseEventsListener* listener : mouse_events_listeners)
						{
							listener->onMouseButtonEvent(evt);
						}

						break;
					}
					case SDL_MOUSEWHEEL:
					{

						IO::MouseWheelEvent evt;

						evt.mouse_id = event.wheel.which;

						evt.delta = event.wheel.y;

						for(ComponentInterfaces::IMouseEventsListener* listener : mouse_events_listeners)
						{
							listener->onMouseWheelEvent(evt);
						}

						break;
					}
					case SDL_MOUSEMOTION:
					{

						IO::MouseMovedEvent evt;

						evt.mouse_id = event.motion.which;

						evt.new_x = event.motion.x;
						evt.new_y = event.motion.y;
						evt.delta_x = event.motion.xrel;
						evt.delta_y = event.motion.yrel;

						for(ComponentInterfaces::IMouseEventsListener* listener : mouse_events_listeners)
						{
							listener->onMouseMoveEvent(evt);
						}

						break;
					}
					case SDL_WINDOWEVENT:
					{
						switch(event.window.event)
						{
							case SDL_WINDOWEVENT_RESIZED:
							{
								for(ComponentInterfaces::WindowEventsListenerComponent* listener : window_events_listeners)
								{
									listener->onWindowResized(event.window.data1, event.window.data2);
								}
								break;
							}
						}
						break;
					}
					case SDL_JOYAXISMOTION:
					{
						IO::JoystickAxisEvent evt;
						evt.axis_id = event.jaxis.axis;
						evt.joystick_id = event.jaxis.which;
						evt.new_value = event.jaxis.value;
						
						for(ComponentInterfaces::IJoystickEventsListener* listener : joystick_events_listeners)
						{
							listener->onJoystickAxisEvent(evt);
						}
						
						break;
					}
					case SDL_JOYBUTTONUP:
					case SDL_JOYBUTTONDOWN:
					{
						IO::JoystickButtonEvent evt;
						evt.joystick_id = event.jbutton.which;
						evt.button_id = event.jbutton.button;
						
						switch(event.jbutton.state)
						{
							case SDL_PRESSED:
							{
								evt.new_state = IO::JoystickButtonState::PRESSED;
								break;
							}
							case SDL_RELEASED:
							{
								evt.new_state = IO::JoystickButtonState::UNPRESSED;
								break;
							}
						}
						
						for(ComponentInterfaces::IJoystickEventsListener* listener : joystick_events_listeners)
						{
							listener->onJoystickButtonEvent(evt);
						}
						
						break;
					}
					default:
					{
						break;
					}
				}
				
			}
			
		}

		void WindowEventsProcessor::addWindowEventsListener ( ComponentInterfaces::WindowEventsListenerComponent* listener )
		{
			window_events_listeners.emplace(listener);
		}

		void WindowEventsProcessor::removeWindowEventsListener ( ComponentInterfaces::WindowEventsListenerComponent* listener )
		{
			window_events_listeners.erase(listener);
		}

		void WindowEventsProcessor::addJoystickEventsListener ( ComponentInterfaces::IJoystickEventsListener* listener )
		{
			joystick_events_listeners.emplace(listener);
		}

		void WindowEventsProcessor::removeJoystickEventsListener ( ComponentInterfaces::IJoystickEventsListener* listener )
		{
			joystick_events_listeners.erase(listener);
		}

		void WindowEventsProcessor::addKeyboardEventsListener ( ComponentInterfaces::IKeyboardEventsListener* listener )
		{
			keyboard_events_listeners.emplace(listener);
		}

		void WindowEventsProcessor::removeKeyboardEventsListener ( ComponentInterfaces::IKeyboardEventsListener* listener )
		{
			keyboard_events_listeners.erase(listener);
		}

		void WindowEventsProcessor::addMouseEventsListener ( ComponentInterfaces::IMouseEventsListener* listener )
		{
			mouse_events_listeners.emplace(listener);
		}

		void WindowEventsProcessor::removeMouseEventsListener ( ComponentInterfaces::IMouseEventsListener* listener )
		{
			mouse_events_listeners.erase(listener);
		}
		
	}
}