#pragma once

#include <LogHelper.h>
#include <ICEGuiSubsystem.h>

namespace UnknownEngine
{
	namespace GUI
	{
		class OgreCEGuiSubsystem : public ICEGuiSubsystem
		{
		public:
			OgreCEGuiSubsystem(const Core::LogHelper &logger);
			~OgreCEGuiSubsystem();
			
			virtual void init();
			virtual void shutdown();
			
		private:
			Core::LogHelper logger;
		};
	}
}