#include <SimpleRotationComponent.h>

#include <ExportedMessages/TransformChangedMessage.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine 
{
	namespace Behavior 
	{
		SimpleRotationComponent::SimpleRotationComponent ( const std::string& name, UnknownEngine::Core::EngineContext* engine_context ) : 
		SimpleBehaviorComponent ( name ),
		transform_changed_message_sender ( GET_OR_CREATE_MESSAGE_SYSTEM_PARTICIPANT_ID(name), engine_context ),
		engine_context(engine_context)
		{
			current_angle = 0;
		}

		SimpleRotationComponent::~SimpleRotationComponent()
		{

		}

		void SimpleRotationComponent::init ( const Core::Entity* parent_entity )
		{
			
		}

		void SimpleRotationComponent::act()
		{
			current_angle += 0.0001;
		
			Core::TransformChangedMessage message;
			message.new_transform.setOrientation( Math::Quaternion(current_angle, Math::Vector3(0,1,0)) );
			
			transform_changed_message_sender.sendMessage(message);
			
		}
		
		void SimpleRotationComponent::shutdown()
		{

		}
	
	}
}