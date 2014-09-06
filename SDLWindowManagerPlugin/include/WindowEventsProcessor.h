#pragma once
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/UserInput/KeyStateChangedMessage.h>
#include <ExportedMessages/RenderSystem/WindowResizedMessage.h>
#include <SDLKeyCodesConverter.h>


namespace UnknownEngine
{
	namespace GUI
	{
		class SDLWindowManager;
		
		class WindowEventsProcessor
		{
		public:
			WindowEventsProcessor(const std::string &name, SDLWindowManager *window_manager, Core::EngineContext* engine_context);
			
			void processEvents();
						
		private:
			Core::MessageSender<IO::KeyStateChangedMessage> key_pressed_message_sender;
			Core::MessageSender<Graphics::WindowResizedMessage> window_resized_message_sender;
			
			IO::SDLKeyCodesConverter keys_converter;

			std::string name;
			SDLWindowManager *window_manager;
		};
	}
}