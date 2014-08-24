#pragma once
#include <MessageSystem/IMessageListener.h>
#include <unordered_map>

namespace UnknownEngine
{
	namespace Behavior
	{

		class SimpleBehaviorComponent;
		
		class SimpleBehaviorUpdateFrameListener : public Core::IMessageListener
		{
		public:
			SimpleBehaviorUpdateFrameListener ( const std::string& object_name );
			virtual ~SimpleBehaviorUpdateFrameListener();
			
			void addSimpleBehaviorComponent(SimpleBehaviorComponent* component);
			void removeSimpleBehaviorComponent(SimpleBehaviorComponent* component);
			
			virtual void processMessage ( const Core::PackedMessage& msg );
			
		private:
			std::unordered_map<std::string, SimpleBehaviorComponent*> behavior_components;
		};
		
	}
}