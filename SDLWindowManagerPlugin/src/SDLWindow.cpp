#include <SDLWindow.h>
#include <WindowEventsProcessor.h>
#include <SDLWindowManager.h>
#include <ComponentSystem/ComponentsManager.h>
#include <SDL_video.h>
#include <SDL_syswm.h>

namespace UnknownEngine
{
	namespace GUI
	{
		SDLWindow::SDLWindow ( const char* name, const SDLWindowDesc& desc, SDLWindowManager* window_manager ) : 
		BaseComponent ( name ),
		window_manager(window_manager),
		desc(desc),
		logger(name, desc.log_level),
		sdl_window(nullptr),
		update_frame_provider(desc.update_frame_provider)
		{
			Core::ComponentsManager::getSingleton()->reserveComponent(window_manager);
		}
		
		SDLWindow::~SDLWindow()
		{
			Core::ComponentsManager::getSingleton()->releaseComponent(window_manager);
		}
		
		void SDLWindow::init ()
		{
			size_t flags = SDL_WINDOW_SHOWN;
			if(desc.resizable) flags |= SDL_WINDOW_RESIZABLE;
			if(desc.full_screen) flags |= SDL_WINDOW_FULLSCREEN;
			sdl_window = SDL_CreateWindow(desc.window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, desc.width, desc.height, flags);
			
			window_events_processor.reset ( new WindowEventsProcessor(getName(), window_manager) );
			
			if(update_frame_provider) update_frame_provider->addListener(this); 
		}

		void SDLWindow::shutdown()
		{
			if(update_frame_provider) update_frame_provider->removeListener(this); 
			
			window_events_processor.reset();
			
			SDL_DestroyWindow(sdl_window);
		}

		Graphics::NativeWindowHandleType SDLWindow::getWindowHandle()
		{
			if(sdl_window != nullptr)
			{
				SDL_SysWMinfo info;
				SDL_VERSION(&info.version);
				
				if(SDL_GetWindowWMInfo(sdl_window, &info))
				{
	#ifdef _MSC_VER
					Graphics::NativeWindowHandleType handle = info.info.win.window;
	#else
					Graphics::NativeWindowHandleType handle = info.info.x11.window;
	#endif
					return handle;
				}
			}
			return Graphics::INVALID_WINDOW_HANDLE;
		}

		const char* SDLWindow::getWindowTitle()
		{
			return desc.window_title.c_str();
		}
		
		Core::IComponentInterface* SDLWindow::getInterface ( const Core::ComponentType& type )
		{
			if(type == ComponentInterfaces::GUIWindowComponent::getTypeName()) return static_cast<ComponentInterfaces::GUIWindowComponent*>(this);
			if(type == ComponentInterfaces::IMouseHandler::getTypeName()) return static_cast<ComponentInterfaces::IMouseHandler*>(this);
			if(type == ComponentInterfaces::IKeyboardHandler::getTypeName()) return static_cast<ComponentInterfaces::IKeyboardHandler*>(this);
			if(type == ComponentInterfaces::IJoystickHandler::getTypeName()) return static_cast<ComponentInterfaces::IJoystickHandler*>(this);
			return nullptr;
		}

		void SDLWindow::addWindowEventsListener ( ComponentInterfaces::WindowEventsListenerComponent* listener )
		{
			if(window_events_processor) window_events_processor->addWindowEventsListener(listener);
		}

		void SDLWindow::removeWindowEventsListener ( ComponentInterfaces::WindowEventsListenerComponent* listener )
		{
			if(window_events_processor) window_events_processor->removeWindowEventsListener(listener);
		}

		void SDLWindow::onUpdateFrame ( Math::Scalar dt )
		{
			if(window_events_processor) window_events_processor->processEvents();
		}
		
		void SDLWindow::addJoystickEventsListener ( ComponentInterfaces::IJoystickEventsListener* listener )
		{
			if(window_events_processor) window_events_processor->addJoystickEventsListener(listener);
		}

		void SDLWindow::addKeyboardEventsListener ( ComponentInterfaces::IKeyboardEventsListener* listener )
		{
			if(window_events_processor) window_events_processor->addKeyboardEventsListener(listener);
		}

		void SDLWindow::addMouseEventsListener ( ComponentInterfaces::IMouseEventsListener* listener )
		{
			if(window_events_processor) window_events_processor->addMouseEventsListener(listener);
		}

		void SDLWindow::removeJoystickEventsListener ( ComponentInterfaces::IJoystickEventsListener* listener )
		{
			if(window_events_processor) window_events_processor->removeJoystickEventsListener(listener);
		}

		void SDLWindow::removeKeyboardEventsListener ( ComponentInterfaces::IKeyboardEventsListener* listener )
		{
			if(window_events_processor) window_events_processor->removeKeyboardEventsListener(listener);
		}

		void SDLWindow::removeMouseEventsListener ( ComponentInterfaces::IMouseEventsListener* listener )
		{
			if(window_events_processor) window_events_processor->removeMouseEventsListener(listener);
		}
		
	}
}