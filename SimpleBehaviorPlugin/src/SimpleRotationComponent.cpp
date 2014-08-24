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
		message_packer( Core::MessageSystemParticipantId(name) )
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
			
			engine_context->getMessageDispatcher()->deliverMessage(message_packer.packMessage(message) );
			
		}
		
		void SimpleRotationComponent::shutdown()
		{

		}
	
	}
}