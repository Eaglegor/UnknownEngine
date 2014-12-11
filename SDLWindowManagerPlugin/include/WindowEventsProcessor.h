#pragma once
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/UserInput/KeyStateChangedMessage.h>
#include <ExportedMessages/UserInput/MouseButtonStateChangedMessage.h>
#include <ExportedMessages/UserInput/MouseMovedMessage.h>
#include <ExportedMessages/UserInput/MouseWheelMovedMessage.h>
#include <ExportedMessages/RenderSystem/WindowResizedMessage.h>
#include <ExportedMessages/UserInput/JoystickAxisMovedMessage.h>
#include <ExportedMessages/UserInput/JoystickButtonStateChanged.h>
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
			Core::MessageSender<IO::MouseButtonStateChangedMessage> mouse_button_pressed_message_sender;
			Core::MessageSender<IO::MouseMovedMessage> mouse_moved_message_sender;
			Core::MessageSender<IO::MouseWheelMovedMessage> mouse_wheel_moved_message_sender;
			Core::MessageSender<IO::JoystickAxisMovedMessage> joystick_axis_moved_message_sender;
			Core::MessageSender<IO::JoystickButtonStateChangedMessage> joystick_button_state_changed_message;
			Core::MessageSender<Graphics::WindowResizedMessage> window_resized_message_sender;
			
			IO::SDLKeyCodesConverter keys_converter;

			std::string name;
			SDLWindowManager *window_manager;
		};
	}
}