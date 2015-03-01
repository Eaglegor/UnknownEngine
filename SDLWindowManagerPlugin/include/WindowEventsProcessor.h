#pragma once
#include <SDLKeyCodesConverter.h>
#include <SDLJoystickWrapper.h>


namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class WindowEventsListenerComponent;
		class IJoystickEventsListener;
		class IMouseEventsListener;
		class IKeyboardEventsListener;
	}
	
	namespace GUI
	{
		class SDLWindowManager;
		
		class WindowEventsProcessor
		{
		public:
			WindowEventsProcessor(const std::string &name, SDLWindowManager *window_manager);
			
			void processEvents();
			
			virtual void addWindowEventsListener ( ComponentInterfaces::WindowEventsListenerComponent* listener );
			virtual void removeWindowEventsListener ( ComponentInterfaces::WindowEventsListenerComponent* listener );
			
			virtual void addJoystickEventsListener ( ComponentInterfaces::IJoystickEventsListener* listener );
			virtual void addKeyboardEventsListener ( ComponentInterfaces::IKeyboardEventsListener* listener );
			virtual void addMouseEventsListener ( ComponentInterfaces::IMouseEventsListener* listener );
			virtual void removeJoystickEventsListener ( ComponentInterfaces::IJoystickEventsListener* listener );
			virtual void removeKeyboardEventsListener ( ComponentInterfaces::IKeyboardEventsListener* listener );
			virtual void removeMouseEventsListener ( ComponentInterfaces::IMouseEventsListener* listener );
			
		private:
			IO::SDLKeyCodesConverter keys_converter;

			std::string name;
			SDLJoystickWrapper joystick_wrapper;
			
			std::unordered_set<ComponentInterfaces::WindowEventsListenerComponent*> window_events_listeners;
			std::unordered_set<ComponentInterfaces::IKeyboardEventsListener*> keyboard_events_listeners;
			std::unordered_set<ComponentInterfaces::IMouseEventsListener*> mouse_events_listeners;
			std::unordered_set<ComponentInterfaces::IJoystickEventsListener*> joystick_events_listeners;
		};
	}
}