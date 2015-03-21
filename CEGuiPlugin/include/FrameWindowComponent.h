#pragma once
#include <ComponentSystem/BaseComponent.h>
#include <ComponentInterfaces/GUI/CEGUI/CEGuiWidgetComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <FrameWindowDesc.h>
#include <BaseCEGuiComponent.h>
#include <LogHelper.h>
#include <Profiling/AverageFpsCounter.h>

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
			
			void updateFps(size_t fps);
			
			FrameWindowDesc desc;
			CEGUI::FrameWindow* window;
			Core::ComponentInterfacePtr<ComponentInterfaces::CEGuiWidgetComponent> parent_widget;
			Core::LogHelper logger;
			
			Utils::AverageFpsCounter fps_counter;
		};
	}
}