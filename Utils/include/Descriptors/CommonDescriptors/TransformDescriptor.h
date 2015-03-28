#pragma once

#include <Descriptors/DescriptorUtils.h>
#include <Transform/Transform.h>
#include <CommonParsers/QuaternionParser.h>
#include <CommonParsers/Vector3Parser.h>

namespace UnknownEngine
{
	namespace Utils
	{
		class TransformDescriptor : public Descriptor
		{
		public:
			using Descriptor::operator=;
			
			OptionalProperty<Math::Vector3> position;
			OptionalProperty<Math::Quaternion> orientation;
			
			operator Math::Transform(){
				Math::Transform transform;
				transform.setPosition(position);
				transform.setOrientation(orientation);
				return transform;
			}
			
			Math::Transform getTransform()
			{
				return static_cast<Math::Transform>(*this);
			}
			
			TransformDescriptor():
			position(0,0,0),
			orientation(Math::Quaternion::Identity())
			{
				UEDESC_ADD_FIELD(position);
				UEDESC_ADD_FIELD(orientation);
			}
		};
	}
}