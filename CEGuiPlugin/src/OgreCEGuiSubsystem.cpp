#include <stdafx.h>

#include <OgreCEGuiSubsystem.h>

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <MessageSystem/MessageSender.h>

namespace UnknownEngine
{
	namespace GUI
	{
		OgreCEGuiSubsystem::OgreCEGuiSubsystem ( const char* name, const Core::LogHelper& logger ):
		logger(logger),
		name(name)
		{
		}
		
		OgreCEGuiSubsystem::~OgreCEGuiSubsystem()
		{
		}

		void OgreCEGuiSubsystem::init()
		{
			
		}

		void OgreCEGuiSubsystem::shutdown()
		{
			
		}
		
	}
}