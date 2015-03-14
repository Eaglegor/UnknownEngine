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
		template<typename T>
		using ConcurrentQueue = LockingConcurrentQueue<T>;
	}
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

			virtual void initComponent(ICEGuiComponent* component) override;
			virtual void shutdownComponent(ICEGuiComponent* component) override;
			virtual void destroyComponent(ICEGuiComponent* component) override;

			typedef std::function<void(Core::IComponent*)> DestructionCallback;
			void startDestruction (DestructionCallback destruction_callback);
			
			virtual void onMouseWheelEvent ( const IO::MouseWheelEvent& evt );
			virtual void onMouseButtonEvent ( const IO::MouseButtonEvent& evt );
			virtual void onMouseMoveEvent ( const IO::MouseMovedEvent& evt );
			virtual void onKeyboardEvent ( const IO::KeyboardEvent& evt );
			
		private:
			void flushInputEvents();
			
			volatile bool is_initialized;
			volatile bool is_waiting_for_shutdown;
			volatile bool is_waiting_for_destruction;
			volatile bool is_shutdown;
			
			Utils::WaitingForEventWrapper waiting_for_initialization;
			Utils::WaitingForEventWrapper waiting_for_destruction;

			Utils::ConcurrentQueue<ICEGuiComponent*> initialization_queue;
			Utils::ConcurrentQueue<ICEGuiComponent*> shutdown_queue;
			Utils::ConcurrentQueue<ICEGuiComponent*> destruction_queue;

			DestructionCallback destruction_callback;			
			
			Utils::ConcurrentQueue<IO::MouseWheelEvent> mouse_wheel_events;
			Utils::ConcurrentQueue<IO::MouseButtonEvent> mouse_button_events;
			Utils::ConcurrentQueue<IO::MouseMovedEvent> mouse_moved_events;
			Utils::ConcurrentQueue<IO::KeyboardEvent> keyboard_events;
		};
	}
}