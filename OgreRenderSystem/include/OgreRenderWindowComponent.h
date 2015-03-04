#pragma once

#include <OgreRenderWindow.h>
#include <OgreRenderSubsystem.h>
#include <Descriptors/OgreRenderWindowDescriptor.h>
#include <Components/BaseOgreComponent.h>
#include <InlineSpecification.h>
#include <ComponentSystem/BaseComponent.h>
#include <ComponentInterfaces/GUI/WindowEventsListenerComponent.h>
#include <ComponentInterfaces/GUI/GUIWindowComponent.h>
#include <ComponentInterfaces/Ogre/IOgreRenderWindowComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <LogHelper.h>
#include <Concurrency/DataStructures/ConcurrentSet.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreRenderWindowComponent : 
			public BaseOgreComponent,
			public ComponentInterfaces::WindowEventsListenerComponent,
			public ComponentInterfaces::IOgreRenderWindowComponent
		{
		public:
			OgreRenderWindowComponent(const char* name, const OgreRenderWindowDescriptor& desc, OgreRenderSubsystem* render_subsystem);
			virtual ~OgreRenderWindowComponent();
			
			constexpr static const char* getTypeName(){return "Ogre.RenderWindow";}
			virtual Core::ComponentType getType() const override {return getTypeName();}
			
			virtual void onWindowResized ( size_t new_width, size_t new_height ) override;
			virtual void onWindowClosed() override;

			virtual Ogre::RenderWindow* getOgreRenderWindow() override
			{
				return render_window;
			}
			
			virtual void _update();
			
			virtual void addListener ( ComponentInterfaces::IRenderWindowEventsListener* listener );
			virtual void removeListener ( ComponentInterfaces::IRenderWindowEventsListener* listener );
			
			virtual IComponentInterface* getInterface ( const Core::ComponentType& type ) override;

		protected:
			virtual void internalInit ();
			virtual void internalShutdown();
			
		private:
			OgreRenderWindowDescriptor desc;
			Core::LogHelper logger;
			OgreRenderSubsystem* render_subsystem;
			Ogre::RenderWindow *render_window;
			
			Ogre::Root *root;
			Core::ComponentInterfacePtr<ComponentInterfaces::GUIWindowComponent> parent_window;
			
			Utils::ConcurrentSet<ComponentInterfaces::IRenderWindowEventsListener*> render_events_listeners;
		};
	}
}