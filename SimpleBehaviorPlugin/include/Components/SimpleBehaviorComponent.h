#pragma once
#include <ComponentSystem/BaseComponent.h>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class SimpleBehaviorComponent : public Core::BaseComponent
		{
		public:
			SimpleBehaviorComponent ( std::string name ):
			Core::BaseComponent(name.c_str())
			{}
			
			virtual void act(Math::Scalar dt) = 0;
		};
	}
}