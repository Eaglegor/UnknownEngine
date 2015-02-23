#pragma once
#include <InlineSpecification.h>
#include <Components/SimpleBehaviorComponent.h>
#include <Descriptors/MouseLookComponentDesc.h>
#include <Transform/Transform.h>
#include <AlignedNew.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/TransformChangedMessage.h>

#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentInterfaces/Input/IContextualActionsMapper.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/Transform/TransformHolderComponent.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
	}

	namespace Behavior
	{
		
		static const Core::ComponentType MOUSE_LOOK_COMPONENT_TYPE = "Behavior.MouseLook";
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) MouseLookComponent : 
			public Core::BaseComponent, 
			public ComponentInterfaces::UpdateFrameListenerComponent,
			public ComponentInterfaces::TransformHolderComponent
		{
		public:
			explicit MouseLookComponent(const std::string& name, const MouseLookComponentDesc& desc );
			virtual ~MouseLookComponent();
				
			UNKNOWNENGINE_INLINE
			virtual Core::ComponentType getType() const override {return MOUSE_LOOK_COMPONENT_TYPE;}
			
			virtual void init ( const Core::IEntity* parent_entity ) override;
			virtual void shutdown() override;
			
			virtual void onUpdateFrame(Math::Scalar dt) override;
			
			void moveForward();
			void moveBackward();
			void strafeLeft();
			void strafeRight();
			void strafeUp();
			void strafeDown();
			void pitch(Math::Scalar amount);
			void yaw(Math::Scalar amount);
			
			virtual Math::Transform getTransform() override;
			virtual Math::Quaternion getOrientation() override;
			virtual Math::Vector3 getPosition() override;
			
			virtual IComponentInterface * getInterface ( const Core::ComponentType & type ) override;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			
			MouseLookComponentDesc desc;
			
			void updateAxisDirections();
			void updateQuaternion();
			
			Core::MessageSender<Core::TransformChangedMessage> transform_changed_message_sender;
			
			Math::Transform current_transform;
			
			Math::Vector3 forward_axis;
			Math::Vector3 right_axis;
			Math::Vector3 up_axis;
			
			Math::Scalar current_x_angle;
			Math::Scalar current_y_angle;
			
			
			bool moving_x_pos;
			bool moving_x_neg;
			bool moving_y_pos;
			bool moving_y_neg;
			bool moving_z_pos;
			bool moving_z_neg;
			
			bool needs_update_quaternion;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
			Core::ComponentInterfacePtr<ComponentInterfaces::IContextualActionsMapper> input_context_mapping_provider;
		};
	}
}