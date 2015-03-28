#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/GUI/CEGUI/CEGuiWidgetComponent.h>

namespace CEGUI
{
	class Window;
}

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class CEGuiParentWidgetComponent : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "CEGuiParentWidgetComponent";}
			
			virtual void addChild(CEGuiWidgetComponent* child) = 0;	
			virtual void removeChild(CEGuiWidgetComponent* child) = 0;
		};
	}
}
