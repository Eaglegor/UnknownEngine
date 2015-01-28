#pragma once

namespace UnknownEngine
{
	namespace GUI
	{
		class ICEGuiSubsystem
		{
		public:
			virtual ~ICEGuiSubsystem(){};
			virtual void init() = 0;
			virtual void shutdown() = 0;
		};
	}
}