#pragma once

#include <InlineSpecification.h>
#include <Quaternion.h>
#include <Vectors/Vector3.h>
#include <AlignedNew.h>

namespace UnknownEngine
{
	namespace Core
	{
		UNKNOWNENGINE_ALIGNED_STRUCT(16) Transform
		{
			public:

				Transform ( const Math::Vector3 &position, const Math::Quaternion &orientation ) :
					position ( position ), orientation ( orientation )
				{}

				Transform() {}

				UNKNOWNENGINE_INLINE
				const Math::Vector3& getPosition() const
				{
					return position;
				}

				UNKNOWNENGINE_INLINE
				void setPosition ( const Math::Vector3 &value )
				{
					position = value;
				}

				UNKNOWNENGINE_INLINE
				const Math::Quaternion getOrientation() const
				{
					return orientation;
				}

				UNKNOWNENGINE_INLINE
				void setOrientation ( const Math::Quaternion &value )
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
				Math::Vector3 position;
				Math::Quaternion orientation;

		};


	}
}
