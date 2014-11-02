#include <SimpleBehaviorsFactory.h>
#include <ComponentDesc.h>
#include <MessageSystem/MessageSystemParticipantDictionary.h>
#include <SimpleRotationComponent.h>
#include <EngineContext.h>
#include <SimpleBehaviorsPerformer.h>
#include <MouseLookComponent.h>

#include <Transform/Transform.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		
		SimpleBehaviorsFactory::SimpleBehaviorsFactory ( UnknownEngine::Core::EngineContext* engine_context, UnknownEngine::Behavior::SimpleBehaviorsPerformer* behaviors_performer ):
		engine_context(engine_context),
		behaviors_performer(behaviors_performer)
		{
			CreatableObjectDesc creatable_component;
			creatable_component.type = SIMPLE_ROTATION_COMPONENT_TYPE;
			creatable_component.creator = std::bind(&SimpleBehaviorsFactory::createSimpleRotationComponent, this, std::placeholders::_1);
			creatable_component.deleter = std::bind(&SimpleBehaviorsFactory::destroySimpleBehaviorComponent, this, std::placeholders::_1);
			registerCreator(creatable_component);
			
			creatable_component.type = MOUSE_LOOK_COMPONENT_TYPE;
			creatable_component.creator = std::bind(&SimpleBehaviorsFactory::createMouseLookComponent, this, std::placeholders::_1);
			creatable_component.deleter = std::bind(&SimpleBehaviorsFactory::destroySimpleBehaviorComponent, this, std::placeholders::_1);
			registerCreator(creatable_component);
		}

		Core::IComponent* SimpleBehaviorsFactory::createSimpleRotationComponent ( const Core::ComponentDesc& desc )
		{
			SimpleRotationComponent* component = new SimpleRotationComponent(desc.name, engine_context);
			behaviors_performer->addSimpleBehaviorComponent(component);
			return component;
		}
		
		Core::IComponent* SimpleBehaviorsFactory::createMouseLookComponent ( const Core::ComponentDesc& desc )
		{
			MouseLookComponent* component = new MouseLookComponent(desc.name, engine_context, Math::Transform( Math::Vector3(0,0,50), Math::Quaternion::Identity() ));
			behaviors_performer->addSimpleBehaviorComponent(component);
			return component;
		}
		
		void SimpleBehaviorsFactory::destroySimpleBehaviorComponent ( Core::IComponent* object )
		{
			behaviors_performer->removeSimpleBehaviorComponent( static_cast<SimpleBehaviorComponent*>(object) );
			delete object;
		}
		
		const char* SimpleBehaviorsFactory::getName()
		{
			return "SimpleBehaviorPlugin.Factories.SimpleBehaviorFactory";
		}

	}
}