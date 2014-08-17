#pragma once

#include <Eigen/Dense>
#include <AlignedNew.h>
#include <InlineSpecification.h>
#include <Scalar.h>
#include <boost/any.hpp>

namespace UnknownEngine
{
	namespace Math
	{
		UNKNOWNENGINE_ALIGNED_CLASS(16) Vector4: public Eigen::Matrix<Scalar, 4, 1>
		{
			public:

				Vector4()
				{
				  setX(0);
				  setY(0);
				  setZ(0);
				}
			  
				Vector4(const Scalar &x, const Scalar &y, const Scalar &z, const Scalar &w)
				{
				  setX(x);
				  setY(y);
				  setZ(z);
				  setW(w);
				}
			  
			    Vector4(const Scalar &x, const Scalar &y, const Scalar &z)
				{
				  setX(x);
				  setY(y);
				  setZ(z);
				  setW(1);
				}
			  
				UNKNOWNENGINE_INLINE
				const Scalar& x() const {return (*this)(0);}

				UNKNOWNENGINE_INLINE
				const Scalar& y() const {return (*this)(1);}

				UNKNOWNENGINE_INLINE
				const Scalar& z() const {return (*this)(2);}

				UNKNOWNENGINE_INLINE
				const Scalar& w() const {return (*this)(3);}
				
				UNKNOWNENGINE_INLINE
				void setX(const Scalar &new_x){(*this)(0) = new_x;}

				UNKNOWNENGINE_INLINE
				void setY(const Scalar &new_y){(*this)(1) = new_y;}

				UNKNOWNENGINE_INLINE
				void setZ(const Scalar &new_z){(*this)(2) = new_z;}

				UNKNOWNENGINE_INLINE
				void setW(const Scalar &new_w){(*this)(3) = new_w;}
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

		};

	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Math::Vector4)