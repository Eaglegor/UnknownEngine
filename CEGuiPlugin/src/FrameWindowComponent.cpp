#include <FrameWindowComponent.h>
#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/WindowManager.h>

namespace UnknownEngine
{
	namespace GUI
	{
		FrameWindowComponent::FrameWindowComponent(const char* name, const FrameWindowDesc &desc) : 
		BaseComponent(name),
		desc(desc),
		window(nullptr),
		parent_widget(desc.parent_window),
		logger(name, desc.log_level)
		{
		}

		bool FrameWindowComponent::init()
		{
			if(!parent_widget)
			{
				LOG_ERROR(logger, "No parent window provided. Can't create component");
				return false;
			}
			
			CEGUI::WindowManager& mgr = CEGUI::WindowManager::getSingleton();
			window = static_cast<CEGUI::FrameWindow*>( mgr.createWindow(desc.window_type.c_str(), getName()) );
			
			if(!window)
			{
				LOG_ERROR(logger, "Failed to initialize frame window");
				return false;
			}
			
			window->setText(desc.window_caption.c_str());
			
			parent_widget->addChild(this);
			
			return true;
		}

		void FrameWindowComponent::shutdown()
		{
			if(window)
			{
				parent_widget->removeChild(this);
				
				LOG_INFO(logger, "Destroying frame window");
				CEGUI::WindowManager::getSingleton().destroyWindow(window);
				LOG_INFO(logger, "Frame window destroyed");
			}
		}

		void FrameWindowComponent::addChild ( ComponentInterfaces::CEGuiWidgetComponent* child )
		{
			window->addChild(child->getCEGuiWindow());
		}

		void FrameWindowComponent::removeChild ( ComponentInterfaces::CEGuiWidgetComponent* child )
		{
			window->removeChild(child->getCEGuiWindow()->getID());
		}

		CEGUI::Window* FrameWindowComponent::getCEGuiWindow()
		{
			return window;
		}

	}
}