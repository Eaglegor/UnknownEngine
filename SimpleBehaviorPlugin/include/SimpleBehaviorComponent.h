#pragma once
#include <Objects/IComponent.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class SimpleBehaviorComponent : public Core::IComponent
		{
		public:
			explicit SimpleBehaviorComponent ( const std::string& name ):
			Core::IComponent(name){}
			
			virtual void act() = 0;
		};
	}
}