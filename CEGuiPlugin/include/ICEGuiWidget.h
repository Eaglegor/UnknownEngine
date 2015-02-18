#pragma once

namespace CEGUI
{
	class Window;
}

namespace UnknownEngine
{
	namespace GUI
	{
		class ICEGuiWidget
		{
		public:
			virtual const char* getName() = 0;
			
			virtual CEGUI::Window* getCEGuiWidget() = 0;
		};
	}
}