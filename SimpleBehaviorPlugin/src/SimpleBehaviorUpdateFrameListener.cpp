#include <SimpleBehaviorUpdateFrameListener.h>
#include <SimpleBehaviorComponent.h>
#include <ExportedMessages/UpdateFrameMessage.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		
		SimpleBehaviorUpdateFrameListener::SimpleBehaviorUpdateFrameListener ( const std::string& object_name ) : IMessageListener ( object_name )
		{
		}

		SimpleBehaviorUpdateFrameListener::~SimpleBehaviorUpdateFrameListener()
		{
		}

		void SimpleBehaviorUpdateFrameListener::processMessage ( const Core::PackedMessage& msg )
		{
			for(auto& component : behavior_components)
			{
				component.second->act();
			}
		}

		void SimpleBehaviorUpdateFrameListener::addSimpleBehaviorComponent ( SimpleBehaviorComponent* component )
		{
			behavior_components.insert(std::make_pair(component->getName(), component));
		}

		void SimpleBehaviorUpdateFrameListener::removeSimpleBehaviorComponent ( SimpleBehaviorComponent* component )
		{
			behavior_components.erase(component->getName());
		}
		
	}
}