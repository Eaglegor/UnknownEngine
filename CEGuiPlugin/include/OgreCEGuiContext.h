#pragma once

#include <LogHelper.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/RenderSystem/Ogre/IOgreRenderWindowComponent.h>
#include <ComponentInterfaces/GUI/CEGUI/CEGuiParentWidgetComponent.h>
#include <ComponentInterfaces/GUI/CEGUI/CEGuiWidgetComponent.h>
#include <ComponentSystem/BaseComponent.h>
#include <OgreRenderTargetListener.h>
#include <Concurrency/WaitingForEventWrapper.h>
#include <ComponentInterfaces/Input/Common/IMouseEventsListener.h>
#include <ComponentInterfaces/Input/Common/IKeyboardEventsListener.h>
#include <ComponentInterfaces/Input/Common/IKeyboardHandler.h>
#include <ComponentInterfaces/Input/Common/IMouseHandler.h>
#include <ComponentInterfaces/GUI/CEGUI/CEGuiContextComponent.h>
#include <Concurrency/DataStructures/ConcurrentSet.h>

namespace CEGUI
{
	class OgreRenderer;
	class Window;
}

namespace UnknownEngine
{
	namespace GUI
	{
		struct OgreCEGuiContextDesc;
		
		class OgreCEGuiContext : 
		public Core::BaseComponent,
		public ComponentInterfaces::CEGuiParentWidgetComponent,
		public ComponentInterfaces::IKeyboardEventsListener,
		public ComponentInterfaces::IMouseEventsListener,
		public ComponentInterfaces::CEGuiContextComponent
		{
		public:
			OgreCEGuiContext(const char* name, const OgreCEGuiContextDesc &desc);
			~OgreCEGuiContext();

			virtual void addChild ( ComponentInterfaces::CEGuiWidgetComponent* child ) override;
			virtual void removeChild ( ComponentInterfaces::CEGuiWidgetComponent* child ) override;
			
			virtual IComponentInterface* getInterface ( const Core::ComponentType& type ) override;

			virtual void onKeyboardEvent ( const IO::KeyboardEvent& evt );
			virtual void onMouseButtonEvent ( const IO::MouseButtonEvent& evt );
			virtual void onMouseMoveEvent ( const IO::MouseMovedEvent& evt );
			virtual void onMouseWheelEvent ( const IO::MouseWheelEvent& evt );

		protected:
			bool initializeRenderer();
			void shutdownRenderer();

			void updateComponents();

			CEGUI::OgreRenderer* renderer;
			CEGUI::Window* main_window;
			Core::LogHelper logger;
			Core::ComponentInterfacePtr<ComponentInterfaces::IOgreRenderWindowComponent> ogre_render_window;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::IKeyboardHandler> keyboard_handler;
			Core::ComponentInterfacePtr<ComponentInterfaces::IMouseHandler> mouse_handler;

			Utils::ConcurrentSet<ICEGuiComponent*> components;
		};
	}
}