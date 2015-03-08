#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace CEGUI
{
	class Window;
}

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class CEGuiWidgetComponent : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "CEGuiWidgetComponent";}
			
			virtual CEGUI::Window* getCEGuiWindow() = 0;
			
			virtual void addChild(CEGuiWidgetComponent* child) = 0;	
			virtual void removeChild(CEGuiWidgetComponent* child) = 0;
		};
	}
}