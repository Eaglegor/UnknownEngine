#pragma once

#include <Eigen/Dense>
#include <AlignedNew.h>
#include <InlineSpecification.h>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace Math
	{
		UNKNOWNENGINE_ALIGNED_CLASS(16) Vector3: public Eigen::Matrix<Scalar, 3, 1>
		{
			public:

				Vector3()
				{
				  setX(0);
				  setY(0);
				  setZ(0);
				}
			  
			        Vector3(const Scalar &x, const Scalar &y, const Scalar &z)
				{
				  setX(x);
				  setY(y);
				  setZ(z);
				}
			  
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

				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

		};
	}
}
