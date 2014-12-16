#pragma once

#include <Scalar.h>
#include <ESInstrumentPort.h>
#include <string>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		static const Math::Scalar DEFAULT_SPEED = 0.1;
		
		struct ESJoystickControllerDesc
		{
			ESInstrumentPort instrument_port;
			uint8_t joystick_id;
			
			Math::Scalar x_axis_speed;
			Math::Scalar y_axis_speed;
			Math::Scalar z_axis_speed;
			Math::Scalar d_axis_speed;
			Math::Scalar branches_speed;
			
			std::string input_context_name;
			std::string x_axis_action_name;
			std::string y_axis_action_name;
			std::string z_axis_left_rotation_action_name;
			std::string z_axis_right_rotation_action_name;
			std::string d_axis_push_action_name;
			std::string d_axis_pull_action_name;
			std::string branches_moved_together_action_name;
			std::string branches_moved_apart_action_name;
			
			ESJoystickControllerDesc():
			x_axis_speed(DEFAULT_SPEED),
			y_axis_speed(DEFAULT_SPEED),
			z_axis_speed(DEFAULT_SPEED),
			d_axis_speed(DEFAULT_SPEED),
			branches_speed(DEFAULT_SPEED),
			x_axis_action_name("XRotation"),
			y_axis_action_name("YRotation"),
			z_axis_left_rotation_action_name("ZLeftRotation"),
			z_axis_right_rotation_action_name("ZRightRotation"),
			d_axis_push_action_name("DAxisPush"),
			d_axis_pull_action_name("DAxisPull"),
			branches_moved_together_action_name("BranchesTogether"),
			branches_moved_apart_action_name("BranchesApart")
			{}
			
		};
	}
}