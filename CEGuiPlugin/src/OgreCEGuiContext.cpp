#include <stdafx.h>

#include <OgreCEGuiContext.h>
#include <OgreCEGuiContextDesc.h>

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace GUI
	{
		OgreCEGuiContext::OgreCEGuiContext ( const char* name, const OgreCEGuiContextDesc &desc ) :
			Core::BaseComponent ( name ),
			renderer ( nullptr ),
			logger ( name, desc.log_level ),
			ogre_render_window ( desc.render_window )
		{
		}

		OgreCEGuiContext::~OgreCEGuiContext()
		{
		}

		bool OgreCEGuiContext::initializeRenderer()
		{
			LOG_INFO ( logger, "Initializing CEGUI Ogre context" );
			renderer = &CEGUI::OgreRenderer::bootstrapSystem ( *ogre_render_window->getOgreRenderWindow() );

			if ( !renderer )
			{
				LOG_ERROR ( logger, "Failed to initialize CEGUI Ogre context" );
				return false;
			}

			LOG_INFO ( logger, "CEGUI Ogre context created" );
			return true;
		}

		void OgreCEGuiContext::shutdownRenderer()
		{
			if(renderer) 
			{
				LOG_INFO(logger, "Destroying CEGUI Ogre context");

				CEGUI::OgreRenderer::destroySystem();
				renderer = nullptr;
				LOG_INFO(logger, "CEGUI Ogre context destroyed");
			}
		}

		
	}
}
