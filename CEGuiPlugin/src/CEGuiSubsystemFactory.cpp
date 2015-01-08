#include <stdafx.h>

#include <CEGuiSubsystemFactory.h>
#include <OgreCEGuiSubsystem.h>

namespace UnknownEngine
{
	namespace GUI
	{
		CEGuiSubsystemFactory::CEGuiSubsystemFactory ( const Core::LogHelper& logger ):
		logger(logger)
		{
		}
		
		ICEGuiSubsystem* CEGuiSubsystemFactory::createSubsystem ( const CEGuiRendererType &renderer_type )
		{
			switch(renderer_type)
			{
				case CEGuiRendererType::OGRE:
				{
					return new OgreCEGuiSubsystem(logger);
					break;
				}
			}
		}

		void CEGuiSubsystemFactory::destroySubsystem ( ICEGuiSubsystem* cegui_subsystem )
		{
			delete cegui_subsystem;
		}
	}
}