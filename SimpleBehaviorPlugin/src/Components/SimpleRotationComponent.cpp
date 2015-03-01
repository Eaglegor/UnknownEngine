#include <stdafx.h>
#include <Components/SimpleRotationComponent.h>

#include <EngineContext.h>
#include <PositionProducerComponent.h>
#include <ComponentInterfaces/Transform/MovableComponent.h>

#include <thread>

namespace UnknownEngine 
{
	using namespace ComponentInterfaces;
	
	namespace Behavior 
	{

		SimpleRotationComponent::SimpleRotationComponent ( const std::string& name, const SimpleRotationComponentDesc& desc) : 
		Core::BaseComponent ( name.c_str() ),
		update_frame_provider(desc.update_frame_provider),
		desc(desc)
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
			
			for(ComponentInterfaces::MovableComponent* listener : listeners)
			{
				listener->setTransform(current_transform);
			}
		}
		
		void SimpleRotationComponent::shutdown()
		{
			if(update_frame_provider) update_frame_provider->removeListener(this);
		}

		Core::IComponentInterface* SimpleRotationComponent::getInterface ( const Core::ComponentType& type )
		{
			if(type == TransformHolderComponent::getTypeName()) return static_cast<TransformHolderComponent*>(this);
			if(type == TransformNotifierComponent::getTypeName()) return static_cast<TransformNotifierComponent*>(this);
			if(type == UpdateFrameListenerComponent::getTypeName()) return static_cast<UpdateFrameListenerComponent*>(this);
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
	
		void SimpleRotationComponent::addListener ( ComponentInterfaces::MovableComponent* movable_component )
		{
			listeners.emplace(movable_component);
		}

		void SimpleRotationComponent::removeListener ( ComponentInterfaces::MovableComponent* movable_component )
		{
			listeners.erase(movable_component);
		}
	
	}
}