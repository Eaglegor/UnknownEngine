#pragma once
#include <ComponentSystem/IComponentInterface.h>
#include <Events/KeyboardEvent.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IKeyboardEventsListener : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "IKeyboardEventsListener";}
			
			virtual void onKeyboardEvent(const IO::KeyboardEvent &evt) = 0;
		};
	}
}