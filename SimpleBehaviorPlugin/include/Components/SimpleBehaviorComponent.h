#pragma once
#include <ComponentSystem/BaseComponent.h>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class SimpleBehaviorComponent : public virtual Core::BaseComponent
		{
		public:
			explicit SimpleBehaviorComponent ( const std::string& name ):
			Core::BaseComponent(name.c_str())
			{}
			
			virtual void act(Math::Scalar dt) = 0;
		};
	}
}