#pragma once

#include <AlignedNew.h>
#include <boost/optional.hpp>
#include <Scalar.h>
#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Physics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT(16) PhysXSubsystemDesc
		{
			bool enable_hardware;
			
			boost::optional<Math::Scalar> tolerances_scale;
			bool track_outstanding_allocations;
			bool enable_profiling;
			bool enable_pvd;
			
			Utils::LogSeverity log_level;
			
			PhysXSubsystemDesc():
			enable_hardware(true),
			track_outstanding_allocations(false),
			enable_profiling(false),
			enable_pvd(false)
			{}
		};
	}
}