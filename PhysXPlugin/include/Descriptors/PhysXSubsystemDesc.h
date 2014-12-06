#pragma once

#include <AlignedNew.h>
#include <boost/optional.hpp>
#include <Scalar.h>
#include <LogSeverity.h>
#include <Vectors/Vector3.h>

namespace UnknownEngine
{
	namespace Physics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT(16) PhysXSubsystemDesc
		{
			bool enable_hardware;
			
			size_t cpu_threads_count;
			
			boost::optional<Math::Scalar> length_tolerance_scale;
			boost::optional<Math::Scalar> mass_tolerance_scale;
			boost::optional<Math::Scalar> speed_tolerance_scale;
			
			bool track_outstanding_allocations;
			bool enable_profiling;
			
			Core::LogSeverity log_level;
			
			Math::Vector3 gravity;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
			PhysXSubsystemDesc():
			enable_hardware(true),
			cpu_threads_count(0),
			track_outstanding_allocations(false),
			enable_profiling(false),
			log_level(Core::LogSeverity::NONE)
			{}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Physics::PhysXSubsystemDesc);