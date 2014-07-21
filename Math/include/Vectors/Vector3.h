#pragma once

#include <Eigen/Dense>
#include <InlineSpecification.h>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace Math
	{
		class Vector3: public Eigen::Matrix<Scalar, 3, 1>
		{
			public:

				UNKNOWNENGINE_INLINE
				const Scalar& x() const {return (*this)(0);}

				UNKNOWNENGINE_INLINE
				const Scalar& y() const {return (*this)(1);}

				UNKNOWNENGINE_INLINE
				const Scalar& z() const {return (*this)(2);}

				UNKNOWNENGINE_INLINE
				void setX(const Scalar &new_x){(*this)(0) = new_x;}

				UNKNOWNENGINE_INLINE
				void setY(const Scalar &new_y){(*this)(1) = new_y;}

				UNKNOWNENGINE_INLINE
				void setZ(const Scalar &new_z){(*this)(2) = new_z;}

		};
	}
}
