#pragma once
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/UserInput/KeyStateChangedMessage.h>
#include "SDLKeyCodesConverter.h"

namespace UnknownEngine
{
	namespace IO
	{
		class KeyboardListener
		{
		public:
			KeyboardListener(const std::string &name, Core::EngineContext* engine_context);
			
			void processEvents();
						
		private:
			Core::MessageSender<IO::KeyStateChangedMessage> key_pressed_message_sender;
			IO::KeyStateChangedMessage msg;
			SDLKeyCodesConverter keys_converter;
			
		};
	}
}