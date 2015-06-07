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
		typedef Eigen::Matrix<Math::Scalar, 2, 1> Vector2;

		static const Vector2 X_AXIS_2D(1, 0);
		static const Vector2 Y_AXIS_2D(0, 1);

	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER ( UnknownEngine::Math::Vector2 )
