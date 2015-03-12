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
		is_waiting_for_destruction(false)
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
				is_waiting_for_destruction = true;
				waiting_for_destruction.wait();
				ogre_render_window->removeListener(this);
			}
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

				if(is_waiting_for_destruction && components.empty())
				{
					if(renderer) shutdownRenderer();
					waiting_for_destruction.notify();
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

	}
}