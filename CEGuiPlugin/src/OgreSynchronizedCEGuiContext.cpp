#include <stdafx.h>

#include <OgreSynchronizedCEGuiContext.h>
#include <OgreCEGuiContextDesc.h>

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace GUI
	{
		OgreSynchronizedCEGuiContext::OgreSynchronizedCEGuiContext (const char* name, const OgreCEGuiContextDesc &desc):
		OgreCEGuiContext(name, desc)
		{
		}
		
		OgreSynchronizedCEGuiContext::~OgreSynchronizedCEGuiContext()
		{
		}

		bool OgreSynchronizedCEGuiContext::init()
		{
			if(!ogre_render_window) 
			{
				LOG_ERROR(logger, "No OGRE render window provided. Can't create context");
				return false;
			}
			
			bool success = initializeRenderer();
			if(!success)
			{
				return false;
			}
			
			return true;
		}

		void OgreSynchronizedCEGuiContext::shutdown()
		{
			shutdownRenderer();
		}

	}
}