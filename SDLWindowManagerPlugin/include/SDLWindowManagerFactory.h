#pragma once

#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace GUI
	{

		class SDLWindow;

		class SDLWindowManager;
		class SDLWindowManagerFactory : public Core::BaseComponentFactory
		{
		public:
			SDLWindowManagerFactory();
			virtual const char* getName() const { return "SDL.WindowManagerFactory"; }
			
		private:
			SDLWindowManager* window_manager;
			SDLWindow* window;
			
			Core::IComponent* createSDLWindowManager(const Core::ComponentDesc &desc);
			Core::IComponent* createSDLWindow(const Core::ComponentDesc &desc);
			
			void destroySDLWindowManager(Core::IComponent* component);
			void destroySDLWindow(Core::IComponent* component);
		};
	}
}