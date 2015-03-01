#pragma once
#include <InlineSpecification.h>
#include <Components/SimpleBehaviorComponent.h>
#include <Quaternion.h>
#include <Vectors/Vector3.h>
#include <AlignedNew.h>
#include <MessageSystem/MessageSender.h>
#include <Descriptors/SimpleRotationComponentDesc.h>

#include <ComponentInterfaces/Transform/TransformHolderComponent.h>
#include <ComponentInterfaces/Transform/TransformNotifierComponent.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>

#include <ComponentSystem/ComponentInterfacePtr.h>

#include <Concurrency/DataStructures/LockingConcurrentSet.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
	}

	namespace Behavior
	{
		UNKNOWNENGINE_ALIGNED_CLASS(16) SimpleRotationComponent : 
			public Core::BaseComponent,
			public ComponentInterfaces::TransformHolderComponent, 
			public ComponentInterfaces::UpdateFrameListenerComponent,
			public ComponentInterfaces::TransformNotifierComponent
		{
		public:
			explicit SimpleRotationComponent ( const std::string& name, const SimpleRotationComponentDesc& desc);
			virtual ~SimpleRotationComponent();
				
			constexpr static const char* getTypeName(){return "Behavior.SimpleRotation";}
			virtual Core::ComponentType getType() const override {return getTypeName();}
			
			virtual bool init () override;
			virtual void shutdown() override;
			
			virtual void onUpdateFrame ( Math::Scalar dt ) override;
			
			virtual Math::Vector3 getPosition() override;
			virtual Math::Quaternion getOrientation() override;
			virtual Math::Transform getTransform() override;
			
			virtual void addListener ( ComponentInterfaces::MovableComponent * movable_component ) override;
			virtual void removeListener ( ComponentInterfaces::MovableComponent * movable_component ) override;
			
			virtual Core::IComponentInterface * getInterface ( const Core::ComponentType & type );
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
			
			SimpleRotationComponentDesc desc;
			
			Utils::LockingConcurrentSet<ComponentInterfaces::MovableComponent*> listeners;
			
			Math::Transform current_transform;
			Math::Scalar current_angle;
			Math::Quaternion quaterion;
		};
	}
}