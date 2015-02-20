#include <stdafx.h>
#include <Components/SimpleRotationComponent.h>

#include <ExportedMessages/TransformChangedMessage.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>
#include <PositionProducerComponent.h>

#include <thread>

namespace UnknownEngine 
{
	namespace Behavior 
	{

		const Core::ComponentType SimpleRotationComponent::component_type("Behavior.SimpleRotationComponent", Utils::PositionProducerComponent::getCType());
		const Core::ComponentType& SimpleRotationComponent::getCType()
		{
			return component_type;
		}

		SimpleRotationComponent::SimpleRotationComponent ( const std::string& name, const SimpleRotationComponentDesc& desc, Core::EngineContext* engine_context ) : 
		SimpleBehaviorComponent ( name ),
		desc(desc),
		transform_changed_message_sender (name),
		engine_context(engine_context)
		{
			current_angle = 0;
		}

		SimpleRotationComponent::~SimpleRotationComponent()
		{

		}

		void SimpleRotationComponent::init ( const Core::IEntity* parent_entity )
		{
			
		}

		void SimpleRotationComponent::act( UnknownEngine::Math::Scalar dt )
		{
			current_angle += 1.0 * dt;
		
			current_transform.setPosition(desc.initial_transform.getPosition());
			current_transform.setOrientation( Math::Quaternion(Math::AngleAxis(current_angle, Math::Vector3(0,1,0))) );
		}
		
		void SimpleRotationComponent::shutdown()
		{

		}

		Math::Vector3 SimpleRotationComponent::getPosition()
		{
			return current_transform.getPosition();
		}

		Math::Quaternion SimpleRotationComponent::getOrientation()
		{
			return current_transform.getOrientation();
		}

		Math::Transform SimpleRotationComponent::getTransform()
		{
			return current_transform;
		}


	
	}
}