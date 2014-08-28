#pragma once
#include <Objects/BaseComponent.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class SimpleBehaviorComponent : public Core::BaseComponent
		{
		public:
			explicit SimpleBehaviorComponent ( const std::string& name ):
			Core::BaseComponent(name)
			{}
			
			virtual void act() = 0;
		};
	}
}