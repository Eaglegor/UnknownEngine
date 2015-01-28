#pragma once

#include <LogHelper.h>
#include <CEGuiRendererType.h>
#include <ICEGuiSubsystem.h>

namespace UnknownEngine
{
	namespace GUI
	{
		class CEGuiSubsystemFactory
		{
		public:
			CEGuiSubsystemFactory(const Core::LogHelper &logger);
			
			ICEGuiSubsystem* createSubsystem(const char* name, const CEGuiRendererType &renderer_type);
			void destroySubsystem(ICEGuiSubsystem* cegui_subsystem);
			
		private:
			Core::LogHelper logger;
		};
	}
}