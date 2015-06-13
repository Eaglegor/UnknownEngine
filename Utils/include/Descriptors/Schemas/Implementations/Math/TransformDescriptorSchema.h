#pragma once

#include <Transform/Transform.h>
#include <Descriptors/Schemas/DescriptorSchema.h>
#include <Descriptors/Schemas/BaseDescriptorSchema.h>
#include <Descriptors/Schemas/Implementations/Math/VectorsFieldSetters.h>
#include <Descriptors/Schemas/Implementations/Math/QuaternionFieldSetter.h>

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
				addField<Math::Vector3>("position", [](Math::Transform &c, const Math::Vector3 &value){c.setPosition(value);}, true);
				addField<Math::Quaternion>("orientation", [](Math::Transform &c, const Math::Quaternion &value){c.setOrientation(value);}, true);
			}
		};
	}
}