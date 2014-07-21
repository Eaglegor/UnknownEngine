#pragma once

#include <InlineSpecification.h>
#include <Quaternion.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct Transform
		{
			public:
				UNKNOWNENGINE_INLINE
				const Math::Position& getPosition() const
				{
					return position;
				}

				UNKNOWNENGINE_INLINE
				void setPosition(const Math::Vector3 &value)
				{
					position = value;
				}

				UNKNOWNENGINE_INLINE
				const Math::Quaternion getOrientation() const
				{
					return orientation;
				}

				UNKNOWNENGINE_INLINE
				void setOrientation(const Math::Quaternion &value)
				{
					orientation = value;
				}

				Transform& operator=(const Transform &rhs)
				{
					if(this==&rhs) return *this;
					this->position = rhs.position;
					this->orientation = rhs.orientation;
					return *this;
				}

			private:
				Math::Vector3 position;
				Math::Quaternion orientation;
		};


	}
}
