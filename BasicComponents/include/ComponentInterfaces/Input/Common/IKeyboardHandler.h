#pragma once
#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{

		class IKeyboardEventsListener;
		class IKeyboardHandler : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "IKeyboardHandler";}
			
			virtual void addKeyboardEventsListener(IKeyboardEventsListener* listener) = 0;
			virtual void removeKeyboardEventsListener(IKeyboardEventsListener* listener) = 0;
		};
	}
}