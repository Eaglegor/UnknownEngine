#pragma once

#include <InlineSpecification.h>
#include <IComponentFactory.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
	}


	namespace Behavior
	{

		class SimpleBehaviorUpdateFrameListener;

		class SimpleRotationComponent;
		
		class SimpleBehaviorsFactory : public Core::IComponentFactory
		{
		public:
			SimpleBehaviorsFactory(SimpleBehaviorUpdateFrameListener* update_frame_listener, Core::EngineContext* engine_context );
			virtual Core::IComponent* createObject ( const Core::ComponentDesc& desc );
			virtual void destroyObject ( Core::IComponent* object );
			virtual const char* getName();	
			
			UNKNOWNENGINE_INLINE
			virtual const std::unordered_set< Core::ComponentType >& getSupportedTypes()
			{
				return supported_types;
			}
			
			UNKNOWNENGINE_INLINE
			virtual const bool supportsType ( const Core::ComponentType& object_type )
			{
				return supported_types.find(object_type) != supported_types.end();
			}
			
		private:
			SimpleRotationComponent* createSimpleRotationComponent(const Core::ComponentDesc& desc);
			
			Core::EngineContext* engine_context;
			std::unordered_set<Core::ComponentType> supported_types;
			SimpleBehaviorUpdateFrameListener* update_frame_listener;
		};
		
	}
}