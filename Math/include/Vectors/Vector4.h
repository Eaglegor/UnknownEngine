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
		typedef Eigen::Matrix<Math::Scalar, 4, 1> Vector4;
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Math::Vector4)