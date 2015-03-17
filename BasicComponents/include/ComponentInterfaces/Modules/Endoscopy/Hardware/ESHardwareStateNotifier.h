#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESHardwareStateListener;
		
		class ESHardwareStateNotifier : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "ESHardwareStateNotifier";}
			
			virtual void addListener(ESHardwareStateListener* listener) = 0;
			virtual void removeListener(ESHardwareStateListener* listener) = 0;
		};
	}
}