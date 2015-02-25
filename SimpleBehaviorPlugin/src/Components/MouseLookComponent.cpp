#include <stdafx.h>
#include <Components/MouseLookComponent.h>

#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>

#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <ExportedMessages/InputContext/AddRangeActionMessage.h>

#include <iostream>

namespace UnknownEngine 
{
	namespace Behavior 
	{
		MouseLookComponent::MouseLookComponent ( const std::string& name, const MouseLookComponentDesc &desc ) : 
		Core::BaseComponent ( name.c_str() ),
		desc(desc),
		transform_changed_message_sender (name),
		current_transform(desc.initial_transform),
		forward_axis(-Math::Z_AXIS),
		right_axis(Math::X_AXIS),
		up_axis(Math::Y_AXIS),
		current_x_angle(0),
		current_y_angle(0),
		moving_x_pos(false),
		moving_x_neg(false),
		moving_y_pos(false),
		moving_y_neg(false),
		moving_z_pos(false),
		moving_z_neg(false),
		needs_update_quaternion(false),
		update_frame_provider(desc.update_frame_provider),
		input_context_mapping_provider(desc.input_context_mapping_provider)
		{
		}

		MouseLookComponent::~MouseLookComponent()
		{

		}

		bool MouseLookComponent::init ()
		{
			if(input_context_mapping_provider)
			{
				const char* input_context_name = desc.input_context_name.c_str();
				
				{
					const char* action_name = desc.move_forward_action_name.c_str();
					auto action_callback = std::bind(&MouseLookComponent::moveForward, this);
					input_context_mapping_provider->addSimpleAction(input_context_name, action_name, action_callback);
				}
				
				{
					const char* action_name = desc.move_backward_action_name.c_str();
					auto action_callback = std::bind(&MouseLookComponent::moveBackward, this);
					input_context_mapping_provider->addSimpleAction(input_context_name, action_name, action_callback);
				}
				
				{
					const char* action_name = desc.strafe_left_action_name.c_str();
					auto action_callback = std::bind(&MouseLookComponent::strafeLeft, this);
					input_context_mapping_provider->addSimpleAction(input_context_name, action_name, action_callback);
				}
				
				{
					const char* action_name = desc.strafe_right_action_name.c_str();
					auto action_callback = std::bind(&MouseLookComponent::strafeRight, this);
					input_context_mapping_provider->addSimpleAction(input_context_name, action_name, action_callback);
				}
				
				{
					const char* action_name = desc.strafe_up_action_name.c_str();
					auto action_callback = std::bind(&MouseLookComponent::strafeUp, this);
					input_context_mapping_provider->addSimpleAction(input_context_name, action_name, action_callback);
				}
				
				{
					const char* action_name = desc.strafe_down_action_name.c_str();
					auto action_callback = std::bind(&MouseLookComponent::strafeDown, this);
					input_context_mapping_provider->addSimpleAction(input_context_name, action_name, action_callback);
				}
				
				{
					const char* action_name = desc.pitch_action_name.c_str();
					auto action_callback = std::bind(&MouseLookComponent::pitch, this, std::placeholders::_1);
					input_context_mapping_provider->addRangedAction(input_context_name, action_name, action_callback);
				}
				
				{
					const char* action_name = desc.yaw_action_name.c_str();
					auto action_callback = std::bind(&MouseLookComponent::yaw, this, std::placeholders::_1);
					input_context_mapping_provider->addRangedAction(input_context_name, action_name, action_callback);
				}
			}

			if(update_frame_provider) update_frame_provider->addListener(this);
			return true;
		}

		void MouseLookComponent::onUpdateFrame( Math::Scalar dt )
		{
			
			Math::Vector3 position_change(0,0,0);
			if(moving_x_neg) position_change -= right_axis * dt * desc.linear_speed;
			if(moving_x_pos) position_change += right_axis * dt * desc.linear_speed;
			if(moving_y_neg) position_change -= up_axis * dt * desc.linear_speed;
			if(moving_y_pos) position_change += up_axis * dt * desc.linear_speed;
			if(moving_z_neg) position_change -= forward_axis * dt*desc.linear_speed;
			if(moving_z_pos) position_change += forward_axis * dt*desc.linear_speed;
			current_transform.setPosition(current_transform.getPosition() + position_change);
			
			moving_x_neg = false;
			moving_x_pos = false;
			moving_y_neg = false;
			moving_y_pos = false;
			moving_z_neg = false;
			moving_z_pos = false;
			
			if(needs_update_quaternion)
			{
				updateQuaternion();
				needs_update_quaternion = false;
			}
			
		}
		
		Math::Quaternion MouseLookComponent::getOrientation()
		{
			return current_transform.getOrientation();
		}
		
		Math::Vector3 MouseLookComponent::getPosition()
		{
			return current_transform.getPosition();
		}

		Math::Transform MouseLookComponent::getTransform()
		{
			return current_transform;
		}
		
		void MouseLookComponent::shutdown()
		{
			if(update_frame_provider) update_frame_provider->removeListener(this);
			
			if(input_context_mapping_provider)
			{
				const char* input_context_name = desc.input_context_name.c_str();
				
				{
					const char* action_name = desc.move_forward_action_name.c_str();
					input_context_mapping_provider->removeSimpleAction(input_context_name, action_name);
				}
				
				{
					const char* action_name = desc.move_backward_action_name.c_str();
					input_context_mapping_provider->removeSimpleAction(input_context_name, action_name);
				}
				
				{
					const char* action_name = desc.strafe_left_action_name.c_str();
					input_context_mapping_provider->removeSimpleAction(input_context_name, action_name);
				}
				
				{
					const char* action_name = desc.strafe_right_action_name.c_str();
					input_context_mapping_provider->removeSimpleAction(input_context_name, action_name);
				}
				
				{
					const char* action_name = desc.strafe_up_action_name.c_str();
					input_context_mapping_provider->removeSimpleAction(input_context_name, action_name);
				}
				
				{
					const char* action_name = desc.strafe_down_action_name.c_str();
					input_context_mapping_provider->removeSimpleAction(input_context_name, action_name);
				}
				
				{
					const char* action_name = desc.pitch_action_name.c_str();
					input_context_mapping_provider->removeRangedAction(input_context_name, action_name);
				}
				
				{
					const char* action_name = desc.yaw_action_name.c_str();
					input_context_mapping_provider->removeRangedAction(input_context_name, action_name);
				}
			}
		}
	
		void MouseLookComponent::moveBackward()
		{
			moving_z_neg = true;
		}
	
		void MouseLookComponent::moveForward()
		{
			moving_z_pos = true;
		}

		void MouseLookComponent::pitch ( Math::Scalar amount )
		{
			current_x_angle -= amount*desc.angular_speed;
			needs_update_quaternion = true;
		}

		void MouseLookComponent::yaw ( Math::Scalar amount )
		{
			current_y_angle -= amount*desc.angular_speed;
			needs_update_quaternion = true;
		}

		void MouseLookComponent::strafeDown()
		{
			moving_y_neg = true;
		}

		void MouseLookComponent::strafeLeft()
		{
			moving_x_neg = true;
		}

		void MouseLookComponent::strafeRight()
		{
			moving_x_pos = true;
		}

		void MouseLookComponent::strafeUp()
		{
			moving_y_pos = true;
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
	
		Core::IComponentInterface* MouseLookComponent::getInterface ( const Core::ComponentType& type )
		{
			if(type == ComponentInterfaces::TransformHolderComponent::getTypeName()) return static_cast<ComponentInterfaces::TransformHolderComponent*>(this);
			return nullptr;
		}
	
	}
}