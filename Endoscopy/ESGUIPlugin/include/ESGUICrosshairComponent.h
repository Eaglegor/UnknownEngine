#pragma once

#include <BaseCEGuiComponent.h>
#include <ESGUICrosshairComponentDesc.h>
#include <ComponentInterfaces/Modules/Endoscopy/GUI/ESGuiCrosshairComponent.h>
#include <ComponentInterfaces/GUI/CEGUI/CEGuiWidgetComponent.h>
#include <ComponentInterfaces/GUI/CEGUI/CEGuiParentWidgetComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <LogHelper.h>


namespace CEGUI
{
	class Window;
}

namespace UnknownEngine
{
	namespace Endoscopy
	{
		class ESGUICrosshairComponent :
		public GUI::BaseCEGuiComponent,
		public ComponentInterfaces::ESGuiCrosshairComponent,
		public ComponentInterfaces::CEGuiWidgetComponent
		{
			public:
				ESGUICrosshairComponent(const char* name, const ESGUICrosshairComponentDesc &desc);

				constexpr static const char* getTypeName(){return "Endoscopy.GUI.Crosshair";}
				virtual Core::ComponentType getType() const {return getTypeName();}

				virtual Core::IComponentInterface *getInterface(const Core::ComponentType &type);

				virtual void _update();

				virtual void setAimed(bool value);

				virtual CEGUI::Window *getCEGuiWindow();

			private:
				virtual void internalInit();
				virtual void internalShutdown();

				ESGUICrosshairComponentDesc desc;

				bool aimed_changed;
				bool new_aimed;

				CEGUI::Window* window;
				CEGUI::Window* image;

				Core::ComponentInterfacePtr<ComponentInterfaces::CEGuiParentWidgetComponent> parent_window;

				Core::LogHelper logger;
		};
	}
}
