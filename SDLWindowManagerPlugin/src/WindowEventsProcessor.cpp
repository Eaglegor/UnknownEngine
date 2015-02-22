#include <stdafx.h>
#include <WindowEventsProcessor.h>
#include <SDLWindowManager.h>
#include <ComponentInterfaces/GUI/WindowEventsListenerComponent.h>

#include <SDL.h>

namespace UnknownEngine
{
	namespace GUI
	{
		WindowEventsProcessor::WindowEventsProcessor ( const std::string& name, SDLWindowManager* window_manager):
		key_pressed_message_sender(name),
		mouse_button_pressed_message_sender(name),
		mouse_moved_message_sender(name),
		mouse_wheel_moved_message_sender(name),
		joystick_axis_moved_message_sender(name),
		joystick_button_state_changed_message(name),
		window_resized_message_sender(name),
		window_manager(window_manager)
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
						
						IO::KeyStateChangedMessage msg;
						
						msg.key = keys_converter.getUnknownEngineKey(event.key.keysym.sym);
						msg.new_state = (event.type == SDL_KEYDOWN ? IO::KeyState::KEY_PRESSED : IO::KeyState::KEY_UNPRESSED);
						
						key_pressed_message_sender.sendMessage(msg);
						
						break;
					}
					case SDL_MOUSEBUTTONDOWN:
					case SDL_MOUSEBUTTONUP:
					{

						IO::MouseButtonStateChangedMessage msg;

						msg.mouse_id = event.button.which;

						msg.new_state = (event.type == SDL_MOUSEBUTTONDOWN ? IO::MouseButtonState::MOUSE_BUTTON_PRESSED : IO::MouseButtonState::MOUSE_BUTTON_UNPRESSED);
						msg.clicks_count = event.button.clicks;

						msg.cursor_position_x = event.button.x;
						msg.cursor_position_y = event.button.y;

						switch(event.button.button)
						{
							case SDL_BUTTON_LEFT:
							{
								msg.button_id = 0;
								break;
							}
							case SDL_BUTTON_RIGHT:
							{
								msg.button_id = 1;
								break;
							}
							case SDL_BUTTON_MIDDLE:
							{
								msg.button_id = 2;
								break;
							}
							case SDL_BUTTON_X1:
							{
								msg.button_id = 3;
								break;
							}
							case SDL_BUTTON_X2:
							{
								msg.button_id = 4;
								break;
							}
						}

						mouse_button_pressed_message_sender.sendMessage(msg);

						break;
					}
					case SDL_MOUSEWHEEL:
					{

						IO::MouseWheelMovedMessage msg;

						msg.mouse_id = event.wheel.which;

						msg.delta_x = event.wheel.x;
						msg.delta_y = event.wheel.y;

						mouse_wheel_moved_message_sender.sendMessage(msg);

						break;
					}
					case SDL_MOUSEMOTION:
					{

						IO::MouseMovedMessage msg;

						msg.mouse_id = event.motion.which;

						msg.new_x = event.motion.x;
						msg.new_y = event.motion.y;
						msg.delta_x = event.motion.xrel;
						msg.delta_y = event.motion.yrel;

						mouse_moved_message_sender.sendMessage(msg);

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
						IO::JoystickAxisMovedMessage msg;
						msg.axis_id = event.jaxis.axis;
						msg.joystick_id = event.jaxis.which;
						msg.new_value = event.jaxis.value;
						
						joystick_axis_moved_message_sender.sendMessage(msg);
						break;
					}
					case SDL_JOYBUTTONUP:
					case SDL_JOYBUTTONDOWN:
					{
						IO::JoystickButtonStateChangedMessage msg;
						msg.joystick_id = event.jbutton.which;
						msg.button_id = event.jbutton.button;
						
						switch(event.jbutton.state)
						{
							case SDL_PRESSED:
							{
								msg.new_state = IO::JoystickButtonState::PRESSED;
								break;
							}
							case SDL_RELEASED:
							{
								msg.new_state = IO::JoystickButtonState::UNPRESSED;
								break;
							}
						}
						
						joystick_button_state_changed_message.sendMessage(msg);
						
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

		
	}
}