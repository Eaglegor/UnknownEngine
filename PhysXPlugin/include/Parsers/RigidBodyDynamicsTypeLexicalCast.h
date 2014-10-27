#pragma once

#include <InlineSpecification.h>
#include <Descriptors/Components/RigidBodyDynamicsType.h>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

namespace boost
{
	typedef UnknownEngine::Physics::RigidBodyDynamicsType UnknownEngineRigidBodyDynamicsType;
	
	template<>
	UNKNOWNENGINE_INLINE
	UnknownEngineRigidBodyDynamicsType lexical_cast<UnknownEngineRigidBodyDynamicsType, std::string>(const std::string& string_value)
	{
		std::string lower_case_string_value = string_value;
		boost::to_lower(lower_case_string_value);
		boost::trim(lower_case_string_value);
		if (lower_case_string_value == "dynamic") return UnknownEngineRigidBodyDynamicsType::DYNAMIC;
		if (lower_case_string_value == "static") return UnknownEngineRigidBodyDynamicsType::STATIC;
		if (lower_case_string_value == "kinematic") return UnknownEngineRigidBodyDynamicsType::KINEMATIC;
		return UnknownEngineRigidBodyDynamicsType::DYNAMIC;
	}
}
