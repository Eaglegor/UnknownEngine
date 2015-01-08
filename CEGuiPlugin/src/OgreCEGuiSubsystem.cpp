#include <stdafx.h>

#include <OgreCEGuiSubsystem.h>

#include <CEGUI/RendererModules/Ogre/Renderer.h>

namespace UnknownEngine
{
	namespace GUI
	{
		OgreCEGuiSubsystem::OgreCEGuiSubsystem ( const Core::LogHelper& logger ):
		logger(logger)
		{
		}
		
		OgreCEGuiSubsystem::~OgreCEGuiSubsystem()
		{
		}

		void OgreCEGuiSubsystem::init()
		{
			CEGUI::OgreRenderer &renderer = CEGUI::OgreRenderer::bootstrapSystem();
		}

		void OgreCEGuiSubsystem::shutdown()
		{
			
		}
		
	}
}