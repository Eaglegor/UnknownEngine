#pragma once

#include <OgreCEGuiContext.h>
#include <ComponentInterfaces/RenderSystem/IRenderWindowEventsListener.h>
#include <Spinlock.h>

namespace CEGUI
{
	class OgreRenderer;
}

namespace UnknownEngine
{
	namespace GUI
	{
		struct OgreCEGuiContextDesc;
		
		class OgreSeparateThreadCEGuiContext : 
		public OgreCEGuiContext,
		public ComponentInterfaces::IRenderWindowEventsListener
		{
		public:
			OgreSeparateThreadCEGuiContext(const char* name, const OgreCEGuiContextDesc &desc);
			~OgreSeparateThreadCEGuiContext();
			
			constexpr static const char* getTypeName(){ return "CEGui.SeparateThreadOgreContext"; }
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual bool init();
			virtual void shutdown();
			
			virtual void onRenderFrame() override;
			
		private:
			volatile bool is_initialized;
			volatile bool is_waiting_for_destruction;
			
			Utils::WaitingForEventWrapper waiting_for_initialization;
			Utils::WaitingForEventWrapper waiting_for_destruction;
		};
	}
}