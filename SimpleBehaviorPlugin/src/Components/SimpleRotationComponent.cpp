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

		SimpleRotationComponent::SimpleRotationComponent ( const std::string& name, const SimpleRotationComponentDesc& desc, Core::EngineContext* engine_context ) : 
		Core::BaseComponent ( name.c_str() ),
		desc(desc),
		engine_context(engine_context),
		update_frame_provider(desc.update_frame_provider)
		{
			current_angle = 0;
		}

		SimpleRotationComponent::~SimpleRotationComponent()
		{

		}

		bool SimpleRotationComponent::init (  )
		{
			if(update_frame_provider) update_frame_provider->addListener(this);
			return true;
		}

		void SimpleRotationComponent::onUpdateFrame( Math::Scalar dt )
		{
			current_angle += 1.0 * dt;
		
			current_transform.setPosition(desc.initial_transform.getPosition());
			current_transform.setOrientation( Math::Quaternion(Math::AngleAxis(current_angle, Math::Vector3(0,1,0))) );
		}
		
		void SimpleRotationComponent::shutdown()
		{
			if(update_frame_provider) update_frame_provider->removeListener(this);
		}

		Core::IComponentInterface* SimpleRotationComponent::getInterface ( const Core::ComponentType& type )
		{
			if(type == ComponentInterfaces::TransformHolderComponent::getTypeName()) return static_cast<ComponentInterfaces::TransformHolderComponent*>(this);
			if(type == ComponentInterfaces::UpdateFrameListenerComponent::getTypeName()) return static_cast<ComponentInterfaces::UpdateFrameListenerComponent*>(this);
			return nullptr;
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