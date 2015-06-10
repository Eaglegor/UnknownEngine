#pragma once

#include <Descriptors/DescriptorUtils.h>
#include <Vectors/Vector3.h>
#include <AxisAlignedBoundingBox.h>
#include <CommonParsers/Vector3Parser.h>

namespace UnknownEngine
{
	namespace Utils
	{
		class AxisAlignedBoundingBoxDescriptor : public Descriptor
		{
		public:
			using Descriptor::operator=;

			RequiredProperty<Math::Vector3> min;
			RequiredProperty<Math::Vector3> max;

			operator Math::AxisAlignedBoudingBox(){
				return getAxisAlignedBoundingBox();
			}

			Math::AxisAlignedBoudingBox getAxisAlignedBoundingBox()
			{
				Math::AxisAlignedBoudingBox aabb;
				aabb.min = min;
				aabb.max = max;
				return aabb;
			}

			AxisAlignedBoundingBoxDescriptor():
			min(0,0,0),
			max(0,0,0)
			{
				UEDESC_ADD_FIELD(min);
				UEDESC_ADD_FIELD(max);
			}
		};
	}
}
