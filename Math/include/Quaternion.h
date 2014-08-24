#pragma once

#include <InlineSpecification.h>
#include <AlignedNew.h>
#include <Eigen/Geometry>
#include <Vectors/Vector3.h>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace Math
	{
		class Quaternion: public Eigen::Quaternion<Scalar>
		{
		public:
		  
			Quaternion()
			{
			  setX(0);
			  setY(0);
			  setZ(0);
			  setW(1);
			}
		  
			Quaternion(const Scalar &x, const Scalar &y, const Scalar &z, const Scalar &w)
			{
			  setX(x);
			  setY(y);
			  setZ(z);
			  setW(w);
			}
		  
			Quaternion(const Scalar& angle, const Math::Vector3& axis):
			Eigen::Quaternion<Scalar>( Eigen::AngleAxis<Scalar>(angle, axis) )
			{
			}
		  
			UNKNOWNENGINE_INLINE
			void setX(const Scalar &new_x){this->x() = new_x;}

			UNKNOWNENGINE_INLINE
			void setY(const Scalar &new_y){this->y() = new_y;}

			UNKNOWNENGINE_INLINE
			void setZ(const Scalar &new_z){this->z() = new_z;}

			UNKNOWNENGINE_INLINE
			void setW(const Scalar &new_w){this->w() = new_w;}

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

		};
	}
}


#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Math::Quaternion)