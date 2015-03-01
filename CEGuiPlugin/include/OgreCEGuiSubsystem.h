#pragma once

#include <LogHelper.h>
#include <ICEGuiSubsystem.h>

namespace CEGUI
{
	class OgreRenderer;
}

namespace UnknownEngine
{
	namespace GUI
	{
		class OgreCEGuiSubsystem : public ICEGuiSubsystem
		{
		public:
			OgreCEGuiSubsystem(const char* name, const Core::LogHelper &logger);
			~OgreCEGuiSubsystem();
			
			virtual void init();
			virtual void shutdown();
			
		private:
			CEGUI::OgreRenderer* renderer;
			Core::LogHelper logger;
			std::string name;
		};
	}
}