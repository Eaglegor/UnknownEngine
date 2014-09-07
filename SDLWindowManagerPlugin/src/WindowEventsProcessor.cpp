#include <WindowEventsProcessor.h>
#include <SDLWindowManager.h>

#include <SDL.h>

namespace UnknownEngine
{
	namespace GUI
	{
		WindowEventsProcessor::WindowEventsProcessor ( const std::string& name, SDLWindowManager* window_manager, UnknownEngine::Core::EngineContext* engine_context ):
		key_pressed_message_sender( GET_OR_CREATE_MESSAGE_SYSTEM_PARTICIPANT_ID(name), engine_context ),
		window_resized_message_sender( GET_OR_CREATE_MESSAGE_SYSTEM_PARTICIPANT_ID(name), engine_context ),
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
						IO::KeyStateChangedMessage msg;
						
						msg.key = keys_converter.getUnknownEngineKey(event.key.keysym.sym);
						msg.new_state = (event.type == SDL_KEYDOWN ? IO::KeyState::KEY_PRESSED : IO::KeyState::KEY_UNPRESSED);
						
						key_pressed_message_sender.sendMessage(msg);
						
						break;
					}
					case SDL_WINDOWEVENT:
					{
						switch(event.window.event)
						{
							case SDL_WINDOWEVENT_RESIZED:
							{
								Graphics::WindowResizedMessage msg;
								msg.window_name = window_manager->getWindowName(event.window.windowID);
								msg.width = event.window.data1;
								msg.height = event.window.data1;
								
								window_resized_message_sender.sendMessage(msg);
								break;
							}
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

	}
}