#pragma once

#include <Scalar.h>
#include <ESInstrumentPort.h>
#include <string>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Endoscopy
	{
		static const Math::Scalar DEFAULT_SPEED = 1;
		static const Math::Scalar DEFAULT_LIMIT = 1;
		
		struct ESJoystickControllerDesc
		{
			ESInstrumentPort instrument_port;
			
			Math::Scalar x_axis_speed;
			Math::Scalar y_axis_speed;
			Math::Scalar z_axis_speed;
			Math::Scalar d_axis_speed;
			Math::Scalar branches_speed;
			
			Math::Scalar x_low_limit;
			Math::Scalar x_high_limit;
			Math::Scalar y_low_limit;
			Math::Scalar y_high_limit;
			Math::Scalar d_low_limit;
			Math::Scalar d_high_limit;
			
			std::string input_context_name;
			std::string x_axis_action_name;
			std::string y_axis_action_name;
			std::string z_axis_left_rotation_action_name;
			std::string z_axis_right_rotation_action_name;
			std::string d_axis_push_action_name;
			std::string d_axis_pull_action_name;
			std::string branches_moved_together_action_name;
			
			Core::IComponent* update_frame_provider;
			Core::IComponent* input_context_mapping_provider;
			
			ESJoystickControllerDesc():
			instrument_port(ESInstrumentPort::CAMERA),
			x_axis_speed(DEFAULT_SPEED),
			y_axis_speed(DEFAULT_SPEED),
			z_axis_speed(DEFAULT_SPEED),
			d_axis_speed(DEFAULT_SPEED),
			branches_speed(DEFAULT_SPEED),
			x_low_limit(-DEFAULT_LIMIT),
			x_high_limit(DEFAULT_LIMIT),
			y_low_limit(-DEFAULT_LIMIT),
			y_high_limit(DEFAULT_LIMIT),
			d_low_limit(-DEFAULT_LIMIT),
			d_high_limit(DEFAULT_LIMIT),
			input_context_name("CameraInstrumentController"),
			x_axis_action_name("XRotation"),
			y_axis_action_name("YRotation"),
			z_axis_left_rotation_action_name("ZLeftRotation"),
			z_axis_right_rotation_action_name("ZRightRotation"),
			d_axis_push_action_name("DAxisPush"),
			d_axis_pull_action_name("DAxisPull"),
			branches_moved_together_action_name("BranchesTogether"),
			update_frame_provider(nullptr),
			input_context_mapping_provider(nullptr)
			{}
			
		};
	}
}