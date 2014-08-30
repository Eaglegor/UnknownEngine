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
		engine_context(engine_context),
		transform_changed_message_sender ( 
			Core::MessageSystemParticipantId(name, Core::MessageSystemParticipantId::AutoRegistrationPolicy::AUTO_REGISTER), 
			engine_context
		)
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
			current_angle += 0.00001;
		
			Core::TransformChangedMessage message;
			message.new_transform.setOrientation( Math::Quaternion(current_angle, Math::Vector3(0,1,0)) );
			
			transform_changed_message_sender.sendMessage(message);
			
		}
		
		void SimpleRotationComponent::shutdown()
		{

		}
	
	}
}