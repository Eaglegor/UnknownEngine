#include <stdafx.h>
#include <Components/SimpleRotationComponent.h>

#include <ExportedMessages/TransformChangedMessage.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine 
{
	namespace Behavior 
	{
		SimpleRotationComponent::SimpleRotationComponent ( const std::string& name, const SimpleRotationComponentDesc& desc, Core::EngineContext* engine_context ) : 
		SimpleBehaviorComponent ( name ),
		desc(desc),
		transform_changed_message_sender (name, engine_context ),
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
		
			Core::TransformChangedMessage message;
			message.new_transform.setPosition(desc.initial_transform.getPosition());
			message.new_transform.setOrientation( Math::Quaternion(Math::AngleAxis(current_angle, Math::Vector3(0,1,0))) );
			
			transform_changed_message_sender.sendMessage(message);
			
		}
		
		void SimpleRotationComponent::shutdown()
		{

		}
	
	}
}