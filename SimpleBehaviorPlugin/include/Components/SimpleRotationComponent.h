#pragma once
#include <InlineSpecification.h>
#include <Components/SimpleBehaviorComponent.h>
#include <Quaternion.h>
#include <Vectors/Vector3.h>
#include <AlignedNew.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <Descriptors/SimpleRotationComponentDesc.h>

#include <ComponentInterfaces/Transform/TransformHolderComponent.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>

#include <ComponentSystem/ComponentInterfacePtr.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
	}

	namespace Behavior
	{
		
		static const Core::ComponentType SIMPLE_ROTATION_COMPONENT_TYPE = Core::ComponentType("Behavior.SimpleRotation");
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) SimpleRotationComponent : 
			public Core::BaseComponent,
			public ComponentInterfaces::TransformHolderComponent, 
			public ComponentInterfaces::UpdateFrameListenerComponent
		{
		public:
			explicit SimpleRotationComponent ( const std::string& name, const SimpleRotationComponentDesc& desc, Core::EngineContext* engine_context );
			virtual ~SimpleRotationComponent();
				
			UNKNOWNENGINE_INLINE
			virtual Core::ComponentType getType() const override {return SIMPLE_ROTATION_COMPONENT_TYPE;}
			
			virtual void init () override;
			virtual void shutdown() override;
			
			virtual void onUpdateFrame ( Math::Scalar dt ) override;
			
			virtual Math::Vector3 getPosition() override;
			virtual Math::Quaternion getOrientation() override;
			virtual Math::Transform getTransform() override;
			
			virtual Core::IComponentInterface * getInterface ( const Core::ComponentType & type );
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
			
			SimpleRotationComponentDesc desc;
						
			Math::Transform current_transform;
			Core::EngineContext* engine_context;
			Math::Scalar current_angle;
			Math::Quaternion quaterion;
		};
	}
}