#include <ESGUIHintComponent.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		static const char* ES_HINT_LABEL_NAME = "HintLabel";
		
		ESGUIHintComponent::ESGUIHintComponent ( const char* name, const ESGUIHintComponentDesc& desc ):
		GUI::BaseCEGuiComponent(name, desc.cegui_context),
		window(nullptr),
		label(nullptr),
		desc(desc),
		text_updated(false),
		parent_window(desc.parent_window),
		logger(name, desc.log_level)
		{
		}

		ESGUIHintComponent::~ESGUIHintComponent()
		{
		}
		
		void ESGUIHintComponent::internalInit()
		{
			if(!parent_window) {
				LOG_ERROR(logger, "No parent window provided. Can't create component");
				return;
			}
			
			window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(desc.layout_filename);
			
			if(!window)
			{
				LOG_ERROR(logger, "Failed to create CEGUI window");
				return;
			}

			try
			{
				label = window->getChild(ES_HINT_LABEL_NAME);
			}
			catch(const CEGUI::UnknownObjectException &e)
			{
				LOG_ERROR(logger, "Failed to retrieve label widget from provided layout. Component not created. CEGUI error:" + e.getMessage().c_str());
				CEGUI::WindowManager::getSingleton().destroyWindow(window);
				window = nullptr;
				return;
			}
			
			parent_window->addChild(this);
			
			if(!desc.default_text.empty())
			{
				setText(desc.default_text.c_str());
			}
		
		}

		void ESGUIHintComponent::internalShutdown()
		{
			if(!window) return;

			CEGUI::WindowManager::getSingleton().destroyWindow(window);
			window = nullptr;
		}

		void ESGUIHintComponent::setText ( const char* text )
		{
			new_text = text;
			text_updated = true;
		}

		void ESGUIHintComponent::_update()
		{
			if(text_updated)
			{
				label->setText(new_text);
				text_updated = false;
			}
		}
		
		void ESGUIHintComponent::addChild ( ComponentInterfaces::CEGuiWidgetComponent* child )
		{
			LOG_ERROR(logger, "Component doesn't support children addition/removal");
		}

		void ESGUIHintComponent::removeChild ( ComponentInterfaces::CEGuiWidgetComponent* child )
		{
			LOG_ERROR(logger, "Component doesn't support children addition/removal");
		}

		CEGUI::Window* ESGUIHintComponent::getCEGuiWindow()
		{
			return window;
		}
		
	}
}
