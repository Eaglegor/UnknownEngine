#pragma once
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/UserInput/KeyStateChangedMessage.h>
#include <ExportedMessages/RenderSystem/WindowResizedMessage.h>
#include <SDLKeyCodesConverter.h>

namespace UnknownEngine
{
	namespace IO
	{
		class WindowEventsListener
		{
		public:
			WindowEventsListener(const std::string &window_name, Core::EngineContext* engine_context);
			
			void processEvents();
						
		private:
			Core::MessageSender<IO::KeyStateChangedMessage> key_pressed_message_sender;
			Core::MessageSender<Graphics::WindowResizedMessage> window_resized_message_sender;
			
			SDLKeyCodesConverter keys_converter;

			std::string window_name;
		};
	}
}