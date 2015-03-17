#pragma once
#include <ComponentSystem/BaseComponent.h>
#include <ComponentInterfaces/CEGUI/CEGuiWidgetComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <FrameWindowDesc.h>
#include "BaseCEGuiComponent.h"
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
		public BaseCEGuiComponent,
		public ComponentInterfaces::CEGuiWidgetComponent
		{
		public:
			FrameWindowComponent( const char* name, const FrameWindowDesc& desc, ICEGuiContext* context );
			~FrameWindowComponent();
			
			constexpr static const char* getTypeName() {return "CEGui.FrameWindowComponent";}
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual void _update();
			
			virtual void addChild ( CEGuiWidgetComponent* child ) override;
			virtual void removeChild ( CEGuiWidgetComponent* child ) override;
			virtual CEGUI::Window* getCEGuiWindow() override;
			
		private:
			virtual void internalInit();
			virtual void internalShutdown();
			
			FrameWindowDesc desc;
			CEGUI::FrameWindow* window;
			Core::ComponentInterfacePtr<ComponentInterfaces::CEGuiWidgetComponent> parent_widget;
			Core::LogHelper logger;
		};
	}
}