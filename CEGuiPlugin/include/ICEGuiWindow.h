#pragma once

namespace UnknownEngine
{
	namespace GUI
	{
		class ICEGuiWidget;
		
		class ICEGuiWindow
		{
		public:
			virtual ~ICEGuiWindow(){}
			
			virtual const char* getName() = 0;
			
			virtual void addWidget(ICEGuiWidget* widget) = 0;
			virtual void removeWidget(ICEGuiWidget* widget) = 0;
		};
	}
}