#pragma once

#include <AlignedNew.h>
#include <Transform/Transform.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		UNKNOWNENGINE_ALIGNED_STRUCT(16) MouseLookComponentDesc
		{
			Math::Transform initial_transform;
			std::string input_context_name;
			
			Math::Scalar linear_speed;
			Math::Scalar angular_speed;
			
			std::string move_forward_action_name;
			std::string move_backward_action_name;
			std::string strafe_left_action_name;
			std::string strafe_right_action_name;
			std::string strafe_up_action_name;
			std::string strafe_down_action_name;
			
			std::string yaw_action_name;
			std::string pitch_action_name;
			
			MouseLookComponentDesc():
			linear_speed(5),
			angular_speed(0.04f),
			move_forward_action_name("MoveForward"),
			move_backward_action_name("MoveBackward"),
			strafe_left_action_name("StrafeLeft"),
			strafe_right_action_name("StrafeRight"),
			strafe_up_action_name("StrafeUp"),
			strafe_down_action_name("StrafeDown"),
			yaw_action_name("Yaw"),
			pitch_action_name("Pitch")
			{
			}
		};
	}
}