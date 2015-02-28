#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ICEGuiWindow.h>

#include <unordered_map>

namespace CEGUI
{
	class Window;
}

namespace UnknownEngine
{
	namespace GUI
	{
		
		class ICEGuiSubsystem;
		
		class CEGuiWindowImpl : public ICEGuiWindow
		{
		public:
			CEGuiWindowImpl(const char* name, ICEGuiSubsystem* gui_subsystem);
			~CEGuiWindowImpl();
			
			virtual void addWidget ( ICEGuiWidget* widget );
			virtual void removeWidget ( ICEGuiWidget* widget );

			virtual void init();
			virtual void shutdown();
			
			virtual const char* getName();
			
		private:
			std::string name;
			//ICEGuiSubsystem* gui_subsystem;
			
			CEGUI::Window* window;
			
			std::unordered_map<std::string, ICEGuiWidget*> widgets;
		};
	}
}