#include <MouseLookComponent.h>

#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>

#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <ExportedMessages/InputContext/AddRangeActionMessage.h>

#include <iostream>

namespace UnknownEngine 
{
	namespace Behavior 
	{
		MouseLookComponent::MouseLookComponent ( const std::string& name, UnknownEngine::Core::EngineContext* engine_context, const Math::Transform &initial_transform ) : 
		SimpleBehaviorComponent ( name ),
		transform_changed_message_sender ( GET_OR_CREATE_MESSAGE_SYSTEM_PARTICIPANT_ID(name), engine_context ),
		engine_context(engine_context),
		forward_axis(-Math::Z_AXIS),
		right_axis(Math::X_AXIS),
		up_axis(Math::Y_AXIS),
		current_x_angle(0),
		current_y_angle(0),
		needs_update_quaternion(false),
		linear_speed(0.001f),
		angular_speed(0.1f),
		current_transform(initial_transform)
		{
		}

		MouseLookComponent::~MouseLookComponent()
		{

		}

		void MouseLookComponent::init ( const Core::Entity* parent_entity )
		{
			{
				Core::MessageSender<IO::AddSimpleActionMessage> simple_action_message_sender
				(
					GET_OR_CREATE_MESSAGE_SYSTEM_PARTICIPANT_ID(getName()),
					engine_context
				);
				
				IO::AddSimpleActionMessage msg;
				msg.context_name = "MouseLook";
				msg.action_slot_name = "MoveForward";
				msg.action_callback = std::bind(&MouseLookComponent::moveForward, this);
				simple_action_message_sender.sendMessage(msg);
				
				msg.action_slot_name = "MoveBackward";
				msg.action_callback = std::bind(&MouseLookComponent::moveBackward, this);
				simple_action_message_sender.sendMessage(msg);
				
				msg.action_slot_name = "StrafeLeft";
				msg.action_callback = std::bind(&MouseLookComponent::strafeLeft, this);
				simple_action_message_sender.sendMessage(msg);
				
				msg.action_slot_name = "StrafeRight";
				msg.action_callback = std::bind(&MouseLookComponent::strafeRight, this);
				simple_action_message_sender.sendMessage(msg);
				
				msg.action_slot_name = "StrafeUp";
				msg.action_callback = std::bind(&MouseLookComponent::strafeUp, this);
				simple_action_message_sender.sendMessage(msg);
				
				msg.action_slot_name = "StrafeDown";
				msg.action_callback = std::bind(&MouseLookComponent::strafeDown, this);
				simple_action_message_sender.sendMessage(msg);
			}
			
			{
				Core::MessageSender<IO::AddRangeActionMessage> range_action_message_sender
				(
					GET_OR_CREATE_MESSAGE_SYSTEM_PARTICIPANT_ID(getName()),
					engine_context
				);
				
				IO::AddRangeActionMessage msg;
				msg.context_name = "MouseLook";
				msg.action_slot_name = "Pitch";
				msg.action_callback = std::bind(&MouseLookComponent::pitch, this, std::placeholders::_1);
				range_action_message_sender.sendMessage(msg);
				
				msg.action_slot_name = "Yaw";
				msg.action_callback = std::bind(&MouseLookComponent::yaw, this, std::placeholders::_1);
				range_action_message_sender.sendMessage(msg);
			}
			
		}

		void MouseLookComponent::act( Math::Scalar dt )
		{
			if(needs_update_quaternion)
			{
				updateQuaternion();
				needs_update_quaternion = false;
			}
			
			Core::TransformChangedMessage message;
			message.new_transform = current_transform;
			
			transform_changed_message_sender.sendMessage(message);
		}
		
		void MouseLookComponent::shutdown()
		{
			
		}
	
		void MouseLookComponent::moveBackward()
		{
			current_transform.setPosition(current_transform.getPosition() - forward_axis*linear_speed);
		}
	
		void MouseLookComponent::moveForward()
		{
			current_transform.setPosition(current_transform.getPosition() + forward_axis*linear_speed);
		}

		void MouseLookComponent::pitch ( Math::Scalar amount )
		{
			current_x_angle -= amount*angular_speed;
			needs_update_quaternion = true;
		}

		void MouseLookComponent::yaw ( Math::Scalar amount )
		{
			current_y_angle -= amount*angular_speed;
			needs_update_quaternion = true;
		}

		void MouseLookComponent::strafeDown()
		{
			current_transform.setPosition(current_transform.getPosition() - up_axis*linear_speed);
		}

		void MouseLookComponent::strafeLeft()
		{
			current_transform.setPosition(current_transform.getPosition() - right_axis*linear_speed);
		}

		void MouseLookComponent::strafeRight()
		{
			current_transform.setPosition(current_transform.getPosition() + right_axis*linear_speed);
		}

		void MouseLookComponent::strafeUp()
		{
			current_transform.setPosition(current_transform.getPosition() + up_axis*linear_speed);
		}
	
		void MouseLookComponent::updateAxisDirections()
		{
			const Math::Quaternion& current_quat = current_transform.getOrientation();
			up_axis = current_quat * (Math::Y_AXIS);
			right_axis = current_quat * (Math::X_AXIS);
			forward_axis = current_quat * (-Math::Z_AXIS);
		}

		void MouseLookComponent::updateQuaternion()
		{
			Math::Quaternion pitch_rotation (Math::AngleAxis(current_x_angle/180*3.14, right_axis));
			Math::Quaternion yaw_rotation (Math::AngleAxis(current_y_angle/180*3.14, up_axis));
			
			current_transform.setOrientation( pitch_rotation * yaw_rotation * current_transform.getOrientation() );
			
			updateAxisDirections();
			
			current_x_angle = 0;
			current_y_angle = 0;
		}
	
	}
}