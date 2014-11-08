#pragma once

#include <string>

namespace UnknownEngine
{
	namespace Behavior
	{
		
		struct SimpleCreateJointComponentDesc
		{
			std::string input_context_name;
			std::string create_joint_action_name;
			
			std::string body1_name;
			std::string body2_name;
			
			std::string jointed_material_name;
			std::string free_material_name;
			
			SimpleCreateJointComponentDesc():
			create_joint_action_name("CreateJoint")
			{
			}
		};
	}
}