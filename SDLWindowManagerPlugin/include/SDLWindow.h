#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ComponentInterfaces/GUI/GUIWindowComponent.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
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
			public ComponentInterfaces::UpdateFrameListenerComponent
		{
		public:
			SDLWindow(const char* name, const SDLWindowDesc &desc, SDLWindowManager* window_manager);
			virtual ~SDLWindow();
			
			constexpr static const char* getTypeName() {return "SDL.Window";}
			virtual Core::ComponentType getType() const override {return getTypeName();}
			
			virtual void init ( const Core::IEntity* parent_entity ) override;
			virtual void shutdown() override;
			
			virtual Graphics::NativeWindowHandleType getWindowHandle() override;
			virtual const char* getWindowTitle() override;
			virtual void addWindowEventsListener ( ComponentInterfaces::WindowEventsListenerComponent* listener );
			virtual void removeWindowEventsListener ( ComponentInterfaces::WindowEventsListenerComponent* listener );
			
			virtual IComponentInterface* getInterface ( const Core::ComponentType& type ) override;
			
			void onUpdateFrame(Math::Scalar dt) override;
			
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