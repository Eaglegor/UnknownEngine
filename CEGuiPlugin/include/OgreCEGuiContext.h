#pragma once

#include <LogHelper.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/Ogre/IOgreRenderWindowComponent.h>
#include <ComponentSystem/BaseComponent.h>

namespace CEGUI
{
	class OgreRenderer;
}

namespace UnknownEngine
{
	namespace GUI
	{
		struct OgreCEGuiContextDesc;
		
		class OgreCEGuiContext : public Core::BaseComponent
		{
		public:
			OgreCEGuiContext(const char* name, const OgreCEGuiContextDesc &desc);
			~OgreCEGuiContext();
			
			virtual bool init();
			virtual void shutdown();
			
			constexpr static const char* getTypeName(){ return "CEGui.OgreContext"; }
			virtual Core::ComponentType getType() const {return getTypeName();}
			
		private:
			CEGUI::OgreRenderer* renderer;
			Core::LogHelper logger;
			Core::ComponentInterfacePtr<ComponentInterfaces::IOgreRenderWindowComponent> ogre_render_window;
		};
	}
}