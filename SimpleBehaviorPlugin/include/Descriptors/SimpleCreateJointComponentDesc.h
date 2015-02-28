#pragma once

#include <string>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
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
			
			Core::IComponent* input_context_mapper;
			Core::IComponent* renderable_component;
			
			SimpleCreateJointComponentDesc():
			create_joint_action_name("CreateJoint"),
			input_context_mapper(nullptr),
			renderable_component(nullptr)
			{
			}
		};
	}
}