#include <WindowEventsListener.h>

#include <SDL.h>

namespace UnknownEngine
{
	namespace IO
	{
		WindowEventsListener::WindowEventsListener ( const std::string& window_name, Core::EngineContext* engine_context ):
		key_pressed_message_sender( 
			Core::MessageSystemParticipantId(window_name, Core::MessageSystemParticipantId::AutoRegistrationPolicy::AUTO_REGISTER),
			engine_context
		),
		window_resized_message_sender( Core::MessageSystemParticipantId(window_name), engine_context )
		{
		}
		
		void WindowEventsListener::processEvents()
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
						msg.new_state = (event.type == SDL_KEYDOWN ? KeyState::KEY_PRESSED : KeyState::KEY_UNPRESSED);
						
						key_pressed_message_sender.sendMessage(msg);
						
						break;
					}
					case SDL_WINDOWEVENT_SIZE_CHANGED:
					{
						Graphics::WindowResizedMessage msg;
						msg.window_name = window_name;
						msg.width = event.window.data1;
						msg.height = event.window.data1;
						
						window_resized_message_sender.sendMessage(msg);
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