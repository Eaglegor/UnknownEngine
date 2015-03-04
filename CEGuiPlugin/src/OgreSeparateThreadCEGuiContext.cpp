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
				if(is_waiting_for_destruction)
				{
					if(renderer) shutdownRenderer();
					waiting_for_destruction.notify();
				}
			}
		}
		
	}
}