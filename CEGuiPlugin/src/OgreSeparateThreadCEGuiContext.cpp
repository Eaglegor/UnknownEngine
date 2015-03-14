#include <stdafx.h>

#include <OgreSeparateThreadCEGuiContext.h>
#include <OgreCEGuiContextDesc.h>

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace GUI
	{
		OgreSeparateThreadCEGuiContext::OgreSeparateThreadCEGuiContext (const char* name, const OgreCEGuiContextDesc &desc):
		OgreCEGuiContext(name, desc),
		is_initialized(false),
		is_waiting_for_shutdown(false),
		is_waiting_for_destruction(false),
		is_shutdown(false)
		{
		}
		
		OgreSeparateThreadCEGuiContext::~OgreSeparateThreadCEGuiContext()
		{
		}

		bool OgreSeparateThreadCEGuiContext::init()
		{
			if(!ogre_render_window) 
			{
				LOG_ERROR(logger, "No OGRE render window provided. Can't create context");
				return false;
			}
			
			ogre_render_window->addListener(this);
			
			waiting_for_initialization.wait();
			
			if(!is_initialized)
			{
				ogre_render_window->removeListener(this);
				return false;
			}
			
			return true;
		}

		void OgreSeparateThreadCEGuiContext::shutdown()
		{
			if(is_initialized)
			{
				is_waiting_for_shutdown = true;
			}
		}

		void OgreSeparateThreadCEGuiContext::startDestruction ( OgreSeparateThreadCEGuiContext::DestructionCallback destruction_callback )
		{
			this->destruction_callback = destruction_callback;
			is_waiting_for_destruction = true;
		}
		
		void OgreSeparateThreadCEGuiContext::onRenderFrame()
		{
			if(!is_initialized)
			{
				is_initialized = initializeRenderer();
				waiting_for_initialization.notify();
			}
			else 
			{

				{//Initialization of components
					int count = initialization_queue.size();
					for(int i = 0; i < count; ++i)
					{
						ICEGuiComponent* component;
						if(initialization_queue.try_pop(component))
						{
							if(component->getState() == ICEGuiComponent::State::INITIALIZATION)
							{
								component->_init();
								components.emplace(component);
							}
							else
							{
								initialization_queue.push(component);
							}
						}
					}
				}

				updateComponents();
				flushInputEvents();

				{//Shutting down of components
					int count = shutdown_queue.size();
					for(int i = 0; i < count; ++i)
					{
						ICEGuiComponent* component;
						if(shutdown_queue.try_pop(component))
						{
							if(component->getState() == ICEGuiComponent::State::SHUTTING_DOWN)
							{
								components.erase(component);
								component->_shutdown();
							}
							else
							{
								shutdown_queue.push(component);
							}
						}
					}
				}

				{//Destruction of components
					int count = destruction_queue.size();
					for(int i = 0; i < count; ++i)
					{
						ICEGuiComponent* component;
						if(destruction_queue.try_pop(component))
						{
							if(component->getState() == ICEGuiComponent::State::DESTRUCTION)
							{
								component->_destroy();
							}
							else
							{
								destruction_queue.push(component);
							}
						}
					}
				}

				if(is_waiting_for_shutdown && components.empty())
				{
					if(renderer) shutdownRenderer();
					is_shutdown = true;
				}
				if(is_shutdown && is_waiting_for_destruction)
				{
					ogre_render_window->removeListener(this);
					destruction_callback(this);
				}
			}
		}

		void OgreSeparateThreadCEGuiContext::initComponent(ICEGuiComponent * component) {
			initialization_queue.push(component);
		}

		void OgreSeparateThreadCEGuiContext::shutdownComponent(ICEGuiComponent * component) {
			shutdown_queue.push(component);
		}

		void OgreSeparateThreadCEGuiContext::destroyComponent(ICEGuiComponent * component) {
			destruction_queue.push(component);
		}

		void OgreSeparateThreadCEGuiContext::onKeyboardEvent ( const IO::KeyboardEvent& evt )
		{
			keyboard_events.push(evt);
		}

		void OgreSeparateThreadCEGuiContext::onMouseButtonEvent ( const IO::MouseButtonEvent& evt )
		{
			mouse_button_events.push(evt);
		}

		void OgreSeparateThreadCEGuiContext::onMouseMoveEvent ( const IO::MouseMovedEvent& evt )
		{
			mouse_moved_events.push(evt);
		}

		void OgreSeparateThreadCEGuiContext::onMouseWheelEvent ( const IO::MouseWheelEvent& evt )
		{
			mouse_wheel_events.push(evt);
		}
		
		void OgreSeparateThreadCEGuiContext::flushInputEvents()
		{
			{
				IO::MouseWheelEvent evt;
				while(mouse_wheel_events.try_pop(evt))
				{
					OgreCEGuiContext::onMouseWheelEvent(evt);
				}
			}
			{
				IO::MouseButtonEvent evt;
				while(mouse_button_events.try_pop(evt))
				{
					OgreCEGuiContext::onMouseButtonEvent(evt);
				}
			}
			{
				IO::MouseMovedEvent evt;
				while(mouse_moved_events.try_pop(evt))
				{
					OgreCEGuiContext::onMouseMoveEvent(evt);
				}
			}
			{
				IO::KeyboardEvent evt;
				while(keyboard_events.try_pop(evt))
				{
					OgreCEGuiContext::onKeyboardEvent(evt);
				}
			}
		}
		
	}
}