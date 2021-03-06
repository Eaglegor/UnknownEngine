#pragma once

#include <AlignedNew.h>
#include <Transform/Transform.h>
#include <Descriptors/Components/RigidBodyDynamicsType.h>
#include <Scalar.h>
#include <boost/optional.hpp>

namespace UnknownEngine
{
	namespace Physics
	{
		class PxShapeDataProvider;

		UNKNOWNENGINE_ALIGNED_STRUCT(16) PxRigidBodyComponentDesc
		{

			PxShapeDataProvider* shape_data_provider;
			Math::Transform local_shape_transform;
			Math::Transform initial_transform;
			RigidBodyDynamicsType dynamics_type;

			Math::Scalar mass;
			
			boost::optional<Math::Scalar> linear_damping;
			boost::optional<Math::Scalar> angular_damping;
			boost::optional<Math::Scalar> max_angular_velocity;
			
			boost::optional<Math::Scalar> stabilization_threshold;
			boost::optional<size_t> position_iterations;
			boost::optional<size_t> velocity_iterations;
			boost::optional<Math::Scalar> contact_report_threshold;

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Physics::PxRigidBodyComponentDesc);