#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ComponentInterfaces/GUI/Common/GUIWindowComponent.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <ComponentInterfaces/Input/Common/IKeyboardHandler.h>
#include <ComponentInterfaces/Input/Common/IMouseHandler.h>
#include <ComponentInterfaces/Input/Common/IJoystickHandler.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <LogHelper.h>
#include <SDLWindowDesc.h>
#include <unordered_set>

struct SDL_Window;
namespace UnknownEngine
{
	namespace GUI
	{

		class WindowEventsProcessor;
		class SDLWindowManager;
		
		class SDLWindow : 
			public Core::BaseComponent, 
			public ComponentInterfaces::GUIWindowComponent,
			public ComponentInterfaces::UpdateFrameListenerComponent,
			public ComponentInterfaces::IKeyboardHandler,
			public ComponentInterfaces::IMouseHandler,
			public ComponentInterfaces::IJoystickHandler
		{
		public:
			SDLWindow(const char* name, const SDLWindowDesc &desc, SDLWindowManager* window_manager);
			virtual ~SDLWindow();
			
			constexpr static const char* getTypeName() {return "SDL.Window";}
			virtual Core::ComponentType getType() const override {return getTypeName();}
			
			virtual bool init () override;
			virtual void shutdown() override;
			
			virtual Graphics::NativeWindowHandleType getWindowHandle() override;
			virtual const char* getWindowTitle() override;
			virtual void addWindowEventsListener ( ComponentInterfaces::WindowEventsListenerComponent* listener ) override;
			virtual void removeWindowEventsListener ( ComponentInterfaces::WindowEventsListenerComponent* listener ) override;
			
			virtual IComponentInterface* getInterface ( const Core::ComponentType& type ) override;
			
			void onUpdateFrame(Math::Scalar dt) override;
			
			virtual void addJoystickEventsListener ( ComponentInterfaces::IJoystickEventsListener* listener ) override;
			virtual void addKeyboardEventsListener ( ComponentInterfaces::IKeyboardEventsListener* listener ) override;
			virtual void addMouseEventsListener ( ComponentInterfaces::IMouseEventsListener* listener ) override;
			virtual void removeJoystickEventsListener ( ComponentInterfaces::IJoystickEventsListener* listener ) override;
			virtual void removeKeyboardEventsListener ( ComponentInterfaces::IKeyboardEventsListener* listener ) override;
			virtual void removeMouseEventsListener ( ComponentInterfaces::IMouseEventsListener* listener ) override;
			
		private:
			SDLWindowManager* window_manager;
			SDLWindowDesc desc;
			Core::LogHelper logger;
			SDL_Window* sdl_window;
			
			std::unique_ptr< WindowEventsProcessor > window_events_processor;
			Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
			
		};
	}
}