#include <KeyboardListener.h>

#include <SDL.h>

namespace UnknownEngine
{
	namespace IO
	{
		KeyboardListener::KeyboardListener ( const std::string& name, Core::EngineContext* engine_context ):
		key_pressed_message_sender( 
			Core::MessageSystemParticipantId(name, Core::MessageSystemParticipantId::AutoRegistrationPolicy::AUTO_REGISTER),
			engine_context
		)
		{
		}
		
		void KeyboardListener::processEvents()
		{
			SDL_Event event;

			while( SDL_PollEvent(&event) )
			{
				switch(event.type)
				{
					case SDL_KEYDOWN:
					case SDL_KEYUP:
					{
						msg.key = keys_converter.getUnknownEngineKey(event.key.keysym.sym);
						msg.new_state = (event.type == SDL_KEYDOWN ? KeyState::KEY_PRESSED : KeyState::KEY_UNPRESSED);
						
						key_pressed_message_sender.sendMessage(msg);
						
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