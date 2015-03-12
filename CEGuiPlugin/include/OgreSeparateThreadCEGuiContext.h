#pragma once

#include <OgreCEGuiContext.h>
#include <ComponentInterfaces/RenderSystem/IRenderWindowEventsListener.h>
#include <Spinlock.h>
#include <Concurrency/DataStructures/LockingConcurrentQueue.h>
#include <Concurrency/DataStructures/ConcurrentSet.h>

namespace CEGUI
{
	class OgreRenderer;
}

namespace UnknownEngine
{
	namespace Utils
	{
		typedef LockingConcurrentQueue ConcurrentQueue;
	}
	namespace GUI
	{
		struct OgreCEGuiContextDesc;
		
		class OgreSeparateThreadCEGuiContext : 
		public OgreCEGuiContext
		{
		public:
			OgreSeparateThreadCEGuiContext(const char* name, const OgreCEGuiContextDesc &desc);
			~OgreSeparateThreadCEGuiContext();
			
			constexpr static const char* getTypeName(){ return "CEGui.SeparateThreadOgreContext"; }
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual bool init();
			virtual void shutdown();
			
			virtual void onRenderFrame() override;

			virtual void initComponent(ICEGuiComponent* component) override;
			virtual void shutdownComponent(ICEGuiComponent* component) override;
			virtual void destroyComponent(ICEGuiComponent* component) override;

		private:
			volatile bool is_initialized;
			volatile bool is_waiting_for_destruction;
			
			Utils::WaitingForEventWrapper waiting_for_initialization;
			Utils::WaitingForEventWrapper waiting_for_destruction;

			Utils::ConcurrentQueue<ICEGuiComponent*> initialization_queue;
			Utils::ConcurrentQueue<ICEGuiComponent*> shutdown_queue;
			Utils::ConcurrentQueue<ICEGuiComponent*> destruction_queue;

		};
	}
}