#include <SDLWindowManagerFactory.h>
#include <SDLWindowManagerDescriptorGetter.h>
#include <SDLWindowDescriptorGetter.h>
#include <SDLWindowManager.h>
#include <SDLWindow.h>
#include <ComponentSystem/ComponentDesc.h>

namespace UnknownEngine
{
	namespace GUI
	{
		static SDLWindowManagerDescriptorGetter sdl_window_manager_descriptor_getter;
		static SDLWindowDescriptorGetter sdl_window_descriptor_getter;
		
		SDLWindowManagerFactory::SDLWindowManagerFactory():
		window_manager(nullptr),
		window(nullptr)
		{
			CreatableObjectDesc creatable_object;
			creatable_object.creator = std::bind(&SDLWindowManagerFactory::createSDLWindowManager, this, std::placeholders::_1);
			creatable_object.deleter = std::bind(&SDLWindowManagerFactory::destroySDLWindowManager, this, std::placeholders::_1);
			creatable_object.type = SDLWindowManager::getTypeName();
			registerCreator(creatable_object);
			
			creatable_object.creator = std::bind(&SDLWindowManagerFactory::createSDLWindow, this, std::placeholders::_1);
			creatable_object.deleter = std::bind(&SDLWindowManagerFactory::destroySDLWindow, this, std::placeholders::_1);
			creatable_object.type = SDLWindow::getTypeName();
			registerCreator(creatable_object);
			
		}

		Core::IComponent* SDLWindowManagerFactory::createSDLWindowManager ( const Core::ComponentDesc& desc )
		{
			if(window_manager) return window_manager;
			SDLWindowManagerDescriptor descriptor = desc.descriptor.apply_visitor(sdl_window_manager_descriptor_getter);
			window_manager = new SDLWindowManager(desc.name, descriptor);
			return window_manager;
		}
		
		Core::IComponent* SDLWindowManagerFactory::createSDLWindow ( const Core::ComponentDesc& desc )
		{
			if(!window_manager || window) return nullptr; // Only one window is supported for now
			SDLWindowDesc descriptor = desc.descriptor.apply_visitor(sdl_window_descriptor_getter);
			SDLWindow* window = new SDLWindow(desc.name.c_str(), descriptor, window_manager);
			return window;
		}
		
		void SDLWindowManagerFactory::destroySDLWindow ( Core::IComponent* component )
		{
			if(component != nullptr)
			{
				delete component;
				window = nullptr;
			}
		}

		void SDLWindowManagerFactory::destroySDLWindowManager ( Core::IComponent* component )
		{
			if(component != nullptr)
			{
				delete component;
				window_manager = nullptr;
			}
		}
	}
}