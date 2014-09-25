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
	UNKNOWNENGINE_ALIGNED_CLASS ( 16 ) Vector3:
		public Eigen::Matrix<Scalar, 3, 1>
		{
		public:

			Vector3()
			{
				setX ( 0 );
				setY ( 0 );
				setZ ( 0 );
			}

			Vector3 ( const Scalar & x, const Scalar & y, const Scalar & z )
			{
				setX ( x );
				setY ( y );
				setZ ( z );
			}

			template<typename T>
			Vector3(const T& rhs):
			Eigen::Matrix<Scalar, 3, 1>(rhs)
			{
			}
			
			UNKNOWNENGINE_INLINE
			const Scalar & x() const {return ( *this ) ( 0 );}

			UNKNOWNENGINE_INLINE
			const Scalar & y() const {return ( *this ) ( 1 );}

			UNKNOWNENGINE_INLINE
			const Scalar & z() const {return ( *this ) ( 2 );}

			UNKNOWNENGINE_INLINE
			void setX ( const Scalar & new_x )
			{
				( *this ) ( 0 ) = new_x;
			}

			UNKNOWNENGINE_INLINE
			void setY ( const Scalar & new_y )
			{
				( *this ) ( 1 ) = new_y;
			}

			UNKNOWNENGINE_INLINE
			void setZ ( const Scalar & new_z )
			{
				( *this ) ( 2 ) = new_z;
			}

			template<typename T>
			UNKNOWNENGINE_INLINE
			Math::Vector3& operator=(const T& rhs)
			{
				Eigen::Matrix<Scalar, 3, 1>::operator=(rhs);
				return *this;
			}

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

		};

		static const Vector3 X_AXIS ( 1, 0, 0 );
		static const Vector3 Y_AXIS ( 0, 1, 0 );
		static const Vector3 Z_AXIS ( 0, 0, 1 );

	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER ( UnknownEngine::Math::Vector3 )
