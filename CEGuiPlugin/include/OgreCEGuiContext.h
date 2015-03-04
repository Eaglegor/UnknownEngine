#pragma once

#include <LogHelper.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/Ogre/IOgreRenderWindowComponent.h>
#include <ComponentSystem/BaseComponent.h>
#include <OgreRenderTargetListener.h>
#include <Concurrency/WaitingForEventWrapper.h>

namespace CEGUI
{
	class OgreRenderer;
}

namespace UnknownEngine
{
	namespace GUI
	{
		struct OgreCEGuiContextDesc;
		
		class OgreCEGuiContext : 
		public Core::BaseComponent
		{
		public:
			OgreCEGuiContext(const char* name, const OgreCEGuiContextDesc &desc);
			~OgreCEGuiContext();
			
		protected:
			bool initializeRenderer();
			void shutdownRenderer();
			
			CEGUI::OgreRenderer* renderer;
			Core::LogHelper logger;
			Core::ComponentInterfacePtr<ComponentInterfaces::IOgreRenderWindowComponent> ogre_render_window;
		};
	}
}