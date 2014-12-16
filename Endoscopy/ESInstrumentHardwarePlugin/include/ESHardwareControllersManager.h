#pragma once

#include <LogHelper.h>
#include <unordered_map>
#include <ESInstrumentPort.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{

		class IESController;
		class ESHardwareControllersManager
		{
		public:
			ESHardwareControllersManager(const Core::LogHelper &log_helper);
			virtual ~ESHardwareControllersManager();
			
			void init();
			void shutdown();
			
		private:
			Core::LogHelper log_helper;
			
			std::unordered_map<ESInstrumentPort, IESController*> controllers;
		};
	}
}