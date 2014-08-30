#pragma once

#include <string>
#include <unordered_set>

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
			void perform();
			
			void addSimpleBehaviorComponent(SimpleBehaviorComponent* component);
			void removeSimpleBehaviorComponent(SimpleBehaviorComponent* component);
			
		private:
			std::unordered_set<SimpleBehaviorComponent*> behavior_components;
			
		};
	}
}