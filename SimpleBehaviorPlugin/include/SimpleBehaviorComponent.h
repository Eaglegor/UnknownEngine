#pragma once
#include <Objects/BaseComponent.h>
#include <Scalar.h>

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
			
			virtual void act(Math::Scalar dt) = 0;
		};
	}
}