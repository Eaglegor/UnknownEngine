#pragma once

#include <Transform/Transform.h>
#include <Descriptors/Schemas/DescriptorSchema.h>
#include <Descriptors/Schemas/BaseDescriptorSchema.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<>
		class DescriptorSchema<Math::Transform> : public BaseDescriptorSchema<Math::Transform>
		{
		public:
			DescriptorSchema()
			{
				
			}
		};
	}
}