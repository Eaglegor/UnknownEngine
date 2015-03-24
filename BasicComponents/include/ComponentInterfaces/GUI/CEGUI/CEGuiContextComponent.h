#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace GUI
	{
		class ICEGuiComponent;
	}
	
	namespace ComponentInterfaces
	{
		class CEGuiContextComponent : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "CEGuiContextComponent";}
			
			virtual void initComponent(GUI::ICEGuiComponent* component) = 0;
			virtual void shutdownComponent(GUI::ICEGuiComponent* component) = 0;
			virtual void destroyComponent(GUI::ICEGuiComponent* component) = 0;
		};
	}
}