#pragma once
#include <InlineSpecification.h>
#include <SimpleBehaviorComponent.h>
#include <Transform/Transform.h>
#include <AlignedNew.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/TransformChangedMessage.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
	}

	namespace Behavior
	{
		
		static const Core::ComponentType MOUSE_LOOK_COMPONENT_TYPE = "Behavior.MouseLook";
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) MouseLookComponent : public SimpleBehaviorComponent
		{
		public:
			explicit MouseLookComponent(const std::string& name, Core::EngineContext* engine_context, const Core::Transform &initial_transform = Core::Transform() );
			virtual ~MouseLookComponent();
				
			UNKNOWNENGINE_INLINE
			virtual Core::ComponentType getType(){return MOUSE_LOOK_COMPONENT_TYPE;}
			
			virtual void init ( const Core::Entity* parent_entity );
			virtual void shutdown();
			
			virtual void act(Math::Scalar dt);
			
			void moveForward();
			void moveBackward();
			void strafeLeft();
			void strafeRight();
			void strafeUp();
			void strafeDown();
			void pitch(Math::Scalar amount);
			void yaw(Math::Scalar amount);
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			
			void updateAxisDirections();
			void updateQuaternion();
			
			Core::MessageSender<Core::TransformChangedMessage> transform_changed_message_sender;
			
			Core::EngineContext* engine_context;
			Core::Transform current_transform;
			
			Math::Vector3 forward_axis;
			Math::Vector3 right_axis;
			Math::Vector3 up_axis;
			
			Math::Scalar current_x_angle;
			Math::Scalar current_y_angle;
			
			bool needs_update_quaternion;
			Math::Scalar linear_speed;
			Math::Scalar angular_speed;
		};
	}
}