#pragma once

#include <Scalar.h>
#include <LogSeverity.h>
#include <boost/optional.hpp>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Physics
	{
		struct PxFixedJointComponentDesc
		{
			Core::IComponent* actor1;
			Core::IComponent* actor2;

			bool use_projection;
			bool collision_enabled;
			boost::optional<Math::Scalar> projection_linear_tolerance;
			boost::optional<Math::Scalar> projection_angular_tolerance;

			Core::LogSeverity log_level = Core::LogSeverity::NONE;
			
			PxFixedJointComponentDesc():
			use_projection(false),
			collision_enabled(false),
			actor1(nullptr),
			actor2(nullptr)
			{}
		};
	}
}
