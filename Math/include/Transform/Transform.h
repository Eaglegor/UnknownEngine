#pragma once

#include <InlineSpecification.h>
#include <Quaternion.h>
#include <Vectors/Vector3.h>
#include <AlignedNew.h>

namespace UnknownEngine
{
	namespace Math
	{
		UNKNOWNENGINE_ALIGNED_STRUCT(16) Transform
		{
			public:

				Transform ( const Vector3 &position, const Quaternion &orientation ) :
					position ( position ), orientation ( orientation )
				{}

				Transform():
				position(0,0,0),
				orientation(Quaternion::Identity())
				{}

				UNKNOWNENGINE_INLINE
				const Vector3& getPosition() const
				{
					return position;
				}

				UNKNOWNENGINE_INLINE
				void setPosition ( const Vector3 &value )
				{
					position = value;
				}

				UNKNOWNENGINE_INLINE
				const Math::Quaternion &getOrientation() const
				{
					return orientation;
				}

				UNKNOWNENGINE_INLINE
				void setOrientation ( const Quaternion &value )
				{
					orientation = value;
				}

				Transform& operator= ( const Transform &rhs )
				{
					if ( this == &rhs ) return *this;
					this->position = rhs.position;
					this->orientation = rhs.orientation;
					return *this;
				}

				UNKNOWNENGINE_INLINE
				static Transform getIdentity()
				{
					return Transform();
				}

				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			private:
				Vector3 position;
				Quaternion orientation;

		};


	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Math::Transform)