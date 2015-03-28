#pragma once

#include <BaseCEGuiComponent.h>
#include <ComponentInterfaces/Modules/Endoscopy/GUI/ESGuiHintComponent.h>
#include <ComponentInterfaces/GUI/CEGUI/CEGuiWidgetComponent.h>
#include <ComponentInterfaces/GUI/CEGUI/CEGuiParentWidgetComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>

#include <ESGUIHintComponentDesc.h>
#include <LogHelper.h>


namespace CEGUI
{
	class Window;
}

namespace UnknownEngine
{
	namespace Endoscopy
	{
		class ESGUIHintComponent : 
		public GUI::BaseCEGuiComponent,
		public ComponentInterfaces::ESGuiHintComponent,
		public ComponentInterfaces::CEGuiWidgetComponent
		{
		public:
			ESGUIHintComponent(const char* name, const ESGUIHintComponentDesc &desc);
			~ESGUIHintComponent();
			
			constexpr static const char* getTypeName(){return "Endoscopy.GUI.Hint";}
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual void internalInit();
			virtual void internalShutdown();
			virtual void _update();
			
			virtual void setText ( const char* text );
			
			virtual CEGUI::Window* getCEGuiWindow();
			
		private:
			CEGUI::Window* window;
			CEGUI::Window* label;
			ESGUIHintComponentDesc desc;
			volatile bool text_updated;
			std::string new_text;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::CEGuiParentWidgetComponent> parent_window;
			
			Core::LogHelper logger;
		};
	}
}