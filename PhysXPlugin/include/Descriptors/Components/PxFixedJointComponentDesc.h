#pragma once

#include <Scalar.h>
#include <boost/optional.hpp>

namespace UnknownEngine
{
	namespace Physics
	{
		struct PxFixedJointComponentDesc
		{
			std::string actor1_name;
			std::string actor2_name;

			bool use_projection;
			bool collision_enabled;
			boost::optional<Math::Scalar> projection_linear_tolerance;
			boost::optional<Math::Scalar> projection_angular_tolerance;

			PxFixedJointComponentDesc():
			use_projection(false),
			collision_enabled(false)
			{}
		};
	}
}
