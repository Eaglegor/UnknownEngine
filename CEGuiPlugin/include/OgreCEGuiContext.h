#pragma once

#include <LogHelper.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/Ogre/IOgreRenderWindowComponent.h>
#include <ComponentInterfaces/CEGUI/CEGuiWidgetComponent.h>
#include <ComponentSystem/BaseComponent.h>
#include <OgreRenderTargetListener.h>
#include <Concurrency/WaitingForEventWrapper.h>
#include <ComponentInterfaces/Input/IMouseEventsListener.h>
#include <ComponentInterfaces/Input/IKeyboardEventsListener.h>
#include <ComponentInterfaces/Input/IKeyboardHandler.h>
#include <ComponentInterfaces/Input/IMouseHandler.h>
#include <ICEGuiContext.h>
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
		public ComponentInterfaces::CEGuiWidgetComponent,
		public ComponentInterfaces::IKeyboardEventsListener,
		public ComponentInterfaces::IMouseEventsListener,
		public ICEGuiContext
		{
		public:
			OgreCEGuiContext(const char* name, const OgreCEGuiContextDesc &desc);
			~OgreCEGuiContext();

			virtual CEGUI::Window* getCEGuiWindow() override;
			virtual void addChild ( CEGuiWidgetComponent* child ) override;
			virtual void removeChild ( CEGuiWidgetComponent* child ) override;
			
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