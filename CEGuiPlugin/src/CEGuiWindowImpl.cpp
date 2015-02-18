#include <CEGuiWindowImpl.h>
#include <ICEGuiWidget.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>

namespace UnknownEngine
{
	namespace GUI
	{
		
		static const char* DEFAULT_WINDOW_LAYOUT_NAME = "DefaultWindow";
		
		CEGuiWindowImpl::CEGuiWindowImpl ( const char* name, ICEGuiSubsystem* gui_subsystem):
		name(name),
		gui_subsystem(gui_subsystem)
		{
			init();
		}

		CEGuiWindowImpl::~CEGuiWindowImpl()
		{
			shutdown();
		}
		
		void CEGuiWindowImpl::addWidget ( ICEGuiWidget* widget )
		{
			auto iter = widgets.find(widget->getName());
			if(iter == widgets.end())
			{
				window->addChild(widget->getCEGuiWidget());
			}
		}

		void CEGuiWindowImpl::removeWidget ( ICEGuiWidget* widget )
		{
			auto iter = widgets.find(widget->getName());
			if(iter != widgets.end())
			{
				window->removeChild(widget->getCEGuiWidget()->getID());
				widgets.erase(iter);
			}
		}

		const char* CEGuiWindowImpl::getName()
		{
			return name.c_str();
		}

		void CEGuiWindowImpl::init ()
		{
			window = CEGUI::WindowManager::getSingleton().createWindow( DEFAULT_WINDOW_LAYOUT_NAME, getName() );
		}

		void CEGuiWindowImpl::shutdown()
		{
			CEGUI::WindowManager::getSingleton().destroyWindow(window);
		}
		
	}
}