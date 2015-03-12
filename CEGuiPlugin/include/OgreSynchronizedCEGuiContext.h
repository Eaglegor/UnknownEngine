#pragma once

#include <OgreCEGuiContext.h>
#include <lmconfig.h>
#include <ComponentInterfaces/RenderSystem/IRenderWindowEventsListener.h>

namespace CEGUI
{
	class OgreRenderer;
}

namespace UnknownEngine
{
	namespace GUI
	{
		struct OgreCEGuiContextDesc;
		
		class OgreSynchronizedCEGuiContext : 
		public OgreCEGuiContext,
		public ComponentInterfaces::IRenderWindowEventsListener
		{
		public:
			OgreSynchronizedCEGuiContext(const char* name, const OgreCEGuiContextDesc &desc);
			~OgreSynchronizedCEGuiContext();
			
			constexpr static const char* getTypeName(){ return "CEGui.SynchronizedOgreContext"; }
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual bool init();
			virtual void shutdown();

			virtual void onRenderFrame() override;

			virtual void initComponent(ICEGuiComponent* component) override;
			virtual void shutdownComponent(ICEGuiComponent* component) override;
			virtual void destroyComponent(ICEGuiComponent* component) override;


		};
	}
}