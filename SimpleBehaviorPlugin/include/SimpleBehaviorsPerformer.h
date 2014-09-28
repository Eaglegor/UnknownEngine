#pragma once

#include <string>
#include <unordered_set>
#include <Scalar.h>

namespace UnknownEngine
{
	
	namespace Core
	{
		class EngineContext;
	}
	
	namespace Behavior
	{
		class SimpleBehaviorComponent;
	
		class SimpleBehaviorsPerformer
		{
		public:
			void perform( Math::Scalar dt );
			
			void addSimpleBehaviorComponent(SimpleBehaviorComponent* component);
			void removeSimpleBehaviorComponent(SimpleBehaviorComponent* component);
			
		private:
			std::unordered_set<SimpleBehaviorComponent*> behavior_components;
			
		};
	}
}