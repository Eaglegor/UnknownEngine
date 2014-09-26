#pragma once

#include <MathPrerequisites.h>

#include <InlineSpecification.h>
#include <Vectors/Vector3.h>
#include <AlignedNew.h>
#include <Eigen/Geometry>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace Math
	{
		typedef Eigen::AngleAxis<Scalar> AngleAxis;
		typedef Eigen::Quaternion < Scalar > Quaternion;
	}
}


#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Math::Quaternion)