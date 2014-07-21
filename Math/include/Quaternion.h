#pragma once

#include <InlineSpecification.h>
#include <Eigen/Geometry>
#include <Scalar.h>

namespace UnknownEngine
{
	namespace Math
	{
		class Quaternion: public Eigen::Quaternion<Scalar>
		{
			UNKNOWNENGINE_INLINE
			void setX(const Scalar &new_x){this->x() = new_x;}

			UNKNOWNENGINE_INLINE
			void setY(const Scalar &new_y){this->y() = new_y;}

			UNKNOWNENGINE_INLINE
			void setZ(const Scalar &new_z){this->z() = new_z;}

			UNKNOWNENGINE_INLINE
			void setW(const Scalar &new_w){this->w() = new_w;}
		};
	}
}
