#pragma once

#include <MathPrerequisites.h>

#include <Eigen/Dense>
#include <AlignedNew.h>
#include <InlineSpecification.h>
#include <Scalar.h>
#include <boost/any.hpp>

namespace UnknownEngine
{
	namespace Math
	{
		typedef Eigen::Matrix<Math::Scalar, 3, 1> Vector3;

		static const Vector3 X_AXIS(1, 0, 0);
		static const Vector3 Y_AXIS(0, 1, 0);
		static const Vector3 Z_AXIS(0, 0, 1);

	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER ( UnknownEngine::Math::Vector3 )
