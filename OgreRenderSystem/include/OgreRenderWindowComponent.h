#pragma once

#include <OgreRenderWindow.h>
#include <OgreRenderSubsystem.h>
#include <Descriptors/OgreRenderWindowDescriptor.h>
#include <InlineSpecification.h>
#include <ComponentSystem/BaseComponent.h>
#include <ComponentInterfaces/GUI/WindowEventsListenerComponent.h>
#include <ComponentInterfaces/GUI/GUIWindowComponent.h>
#include <ComponentInterfaces/Ogre/IOgreRenderWindowComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreRenderWindowComponent : 
			public Core::BaseComponent,
			public ComponentInterfaces::WindowEventsListenerComponent,
			public ComponentInterfaces::IOgreRenderWindowComponent
		{
		public:
			OgreRenderWindowComponent(const char* name, const OgreRenderWindowDescriptor& desc, OgreRenderSubsystem* render_subsystem);
			virtual ~OgreRenderWindowComponent();
			
			constexpr static const char* getTypeName(){return "Ogre.RenderWindow";}
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual void init ( const Core::IEntity* parent_entity );
			virtual void shutdown();
			
			virtual void onWindowResized ( size_t new_width, size_t new_height );

			virtual Ogre::RenderWindow* getOgreRenderWindow() override
			{
				return render_window;
			}
			
			virtual IComponentInterface* getInterface ( const Core::ComponentType& type );
			
		private:
			OgreRenderWindowDescriptor desc;
			Core::LogHelper logger;
			OgreRenderSubsystem* render_subsystem;
			Ogre::RenderWindow *render_window;
			
			Ogre::Root *root;
			Core::ComponentInterfacePtr<ComponentInterfaces::GUIWindowComponent> parent_window;
		};
	}
}