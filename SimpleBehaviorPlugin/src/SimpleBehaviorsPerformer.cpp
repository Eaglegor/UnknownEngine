#include <stdafx.h>
#include <SimpleBehaviorsPerformer.h>
#include <SimpleBehaviorComponent.h>

namespace UnknownEngine
{
	namespace Behavior
	{

		void SimpleBehaviorsPerformer::addSimpleBehaviorComponent ( SimpleBehaviorComponent* component )
		{
			behavior_components.insert(component);
		}
		
		void SimpleBehaviorsPerformer::removeSimpleBehaviorComponent ( SimpleBehaviorComponent* component )
		{
			behavior_components.erase(component);
		}
		
		void SimpleBehaviorsPerformer::perform(Math::Scalar dt)
		{
			for(auto component : behavior_components)
			{
				component->act(dt);
			}
		}
		
	}
}