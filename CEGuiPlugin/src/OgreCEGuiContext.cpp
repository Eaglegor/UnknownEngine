#include <stdafx.h>

#include <OgreCEGuiContext.h>
#include <OgreCEGuiContextDesc.h>

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace GUI
	{
		OgreCEGuiContext::OgreCEGuiContext (const char* name, const OgreCEGuiContextDesc &desc):
		Core::BaseComponent(name),
		logger(name, desc.log_level),
		ogre_render_window(desc.render_window),
		renderer(nullptr)
		{
		}
		
		OgreCEGuiContext::~OgreCEGuiContext()
		{
		}

		bool OgreCEGuiContext::init()
		{
			if(!ogre_render_window) 
			{
				LOG_ERROR(logger, "No OGRE render window provided. Can't create context");
				return false;
			}
			
			renderer = &CEGUI::OgreRenderer::bootstrapSystem(*ogre_render_window->getOgreRenderWindow());
			
			if(!renderer)
			{
				LOG_ERROR(logger, "Failed to initialize CEGUI Ogre context");
				return false;
			}
			
			LOG_INFO(logger, "CEGUI Ogre context created");
			
			return true;
		}

		void OgreCEGuiContext::shutdown()
		{
			if(renderer) 
			{
				LOG_INFO(logger, "Destroying CEGUI Ogre context");
				
				CEGUI::OgreRenderer::destroySystem();
				
				LOG_INFO(logger, "CEGUI Ogre context destroyed");
			}
		}
		
	}
}