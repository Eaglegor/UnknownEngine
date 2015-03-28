#include <ESGUICrosshairComponent.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/ImageManager.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{

		static const char* ES_CROSSHAIR_IMAGE_NAME = "CrosshairImage";

		ESGUICrosshairComponent::ESGUICrosshairComponent(const char *name, const ESGUICrosshairComponentDesc &desc):
		GUI::BaseCEGuiComponent(name, desc.cegui_context),
		desc(desc),
		aimed_changed(false),
		new_aimed(false),
		window(nullptr),
		parent_window(desc.parent_window),
		logger(name, desc.log_level)
		{
		}

		Core::IComponentInterface *ESGUICrosshairComponent::getInterface(const Core::ComponentType &type)
		{
			using namespace ComponentInterfaces;
			if(type == ESGuiCrosshairComponent::getType()) return static_cast<ESGuiCrosshairComponent*>(this);
			return nullptr;
		}

		void ESGUICrosshairComponent::_update()
		{
			if(aimed_changed)
			{
				std::string new_value = desc.imageset_name.get() + "/" + (new_aimed ? desc.aimed_image_name.get() : desc.free_image_name.get());
				image->setProperty("Image", new_value);
				aimed_changed = false;
			}
		}

		void ESGUICrosshairComponent::internalInit()
		{
			if(!parent_window) {
				LOG_ERROR(logger, "No parent window provided. Can't create component");
				return;
			}

			window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(desc.layout_filename.get());

			if(!window)
			{
				LOG_ERROR(logger, "Failed to create CEGUI window");
				return;
			}

			try
			{
				image = window->getChild(ES_CROSSHAIR_IMAGE_NAME);
			}
			catch(const CEGUI::UnknownObjectException &e)
			{
				LOG_ERROR(logger, "Failed to retrieve crosshair image from provided layout. Component not created. CEGUI error:" + e.getMessage().c_str());
				CEGUI::WindowManager::getSingleton().destroyWindow(window);
				window = nullptr;
				return;
			}

			setAimed(false);
			
			parent_window->addChild(this);
		}

		void ESGUICrosshairComponent::internalShutdown()
		{
			if(!window) return;

			CEGUI::WindowManager::getSingleton().destroyWindow(window);
			window = nullptr;
		}

		void ESGUICrosshairComponent::setAimed(bool value)
		{
			new_aimed = value;
			aimed_changed = true;
		}

		CEGUI::Window *ESGUICrosshairComponent::getCEGuiWindow()
		{
			return window;
		}

	}
}
