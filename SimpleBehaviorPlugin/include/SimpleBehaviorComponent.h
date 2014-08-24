#pragma once
#include <Objects/Component.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class SimpleBehaviorComponent : public Core::Component
		{
		public:
			explicit SimpleBehaviorComponent ( const std::string& name ):
			Core::Component(name){}
			
			virtual void act() = 0;
		};
	}
}