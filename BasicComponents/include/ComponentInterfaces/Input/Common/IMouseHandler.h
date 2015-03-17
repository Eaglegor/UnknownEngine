#pragma once
#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{

		class IMouseEventsListener;
		class IMouseHandler : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "IMouseHandler";}
			
			virtual void addMouseEventsListener(IMouseEventsListener* listener) = 0;
			virtual void removeMouseEventsListener(IMouseEventsListener* listener) = 0;
		};
	}
}