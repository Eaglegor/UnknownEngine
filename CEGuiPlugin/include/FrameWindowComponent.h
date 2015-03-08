#pragma once
#include <ComponentSystem/BaseComponent.h>
#include <ComponentInterfaces/CEGUI/CEGuiWidgetComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <FrameWindowDesc.h>
#include <LogHelper.h>

namespace CEGUI
{
	class FrameWindow;
}

namespace UnknownEngine
{
	namespace GUI
	{
		class FrameWindowComponent : 
		public Core::BaseComponent,
		public ComponentInterfaces::CEGuiWidgetComponent
		{
		public:
			FrameWindowComponent(const char* name, const FrameWindowDesc &desc);
			
			virtual bool init() override;
			virtual void shutdown() override;
			
			virtual void addChild ( CEGuiWidgetComponent* child );
			virtual void removeChild ( CEGuiWidgetComponent* child );
			
			virtual CEGUI::Window* getCEGuiWindow();
			
			constexpr static const char* getTypeName() {return "CEGui.FrameWindowComponent";}
			virtual Core::ComponentType getType() const {return getTypeName();}
			
		private:
			FrameWindowDesc desc;
			CEGUI::FrameWindow* window;
			Core::ComponentInterfacePtr<ComponentInterfaces::CEGuiWidgetComponent> parent_widget;
			Core::LogHelper logger;
		};
	}
}