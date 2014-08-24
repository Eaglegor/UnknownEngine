#include <SimpleBehaviorsFactory.h>
#include <ComponentDesc.h>
#include <MessageSystem/MessageSystemParticipantDictionary.h>
#include <SimpleRotationComponent.h>
#include <SimpleBehaviorUpdateFrameListener.h>
#include <EngineContext.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		
		SimpleBehaviorsFactory::SimpleBehaviorsFactory ( UnknownEngine::Behavior::SimpleBehaviorUpdateFrameListener* update_frame_listener, UnknownEngine::Core::EngineContext* engine_context ):
		update_frame_listener(update_frame_listener),
		engine_context(engine_context)
		{
			supported_types.insert(SIMPLE_ROTATION_COMPONENT_TYPE);
		}
		
		Core::Component* SimpleBehaviorsFactory::createObject ( const Core::ComponentDesc& desc )
		{
			SimpleBehaviorComponent* component = nullptr;
			if(desc.type == SIMPLE_ROTATION_COMPONENT_TYPE)
			{
				 component = createSimpleRotationComponent(desc);
				 update_frame_listener->addSimpleBehaviorComponent(component);
			}
			return component;
		}

		void SimpleBehaviorsFactory::destroyObject ( Core::Component* object )
		{
			SimpleBehaviorComponent* component = dynamic_cast<SimpleBehaviorComponent*>(object);
			if(component != nullptr && object->getType() == SIMPLE_ROTATION_COMPONENT_TYPE)
			{
				update_frame_listener->removeSimpleBehaviorComponent(component);
				delete object;
			}
		}

		const std::string SimpleBehaviorsFactory::getName()
		{
			return "SimpleBehaviorPlugin.SimpleBehaviorFactory";
		}
		
		SimpleRotationComponent* SimpleBehaviorsFactory::createSimpleRotationComponent ( const Core::ComponentDesc& desc )
		{
			engine_context->getMessageSystemParticipantDictionary()->registerNewMessageParticipant(desc.name);
			return new SimpleRotationComponent(desc.name, engine_context);
		}
	}
}