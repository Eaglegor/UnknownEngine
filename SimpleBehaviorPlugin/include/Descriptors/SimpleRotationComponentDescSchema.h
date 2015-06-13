#pragma once

#include <Descriptors/Schemas/DescriptorSchema.h>
#include <Descriptors/Schemas/BaseDescriptorSchema.h>
#include <Descriptors/SimpleRotationComponentDesc.h>

#include <Transform/TransformDescriptorSchema.h>
#include <Descriptors/Schemas/DefaultSetters/DefaultDescriptorFieldSetters.h>
#include <Descriptors/Schemas/DefaultSetters/IComponentFieldSetter.h>


namespace UnknownEngine
{
	namespace Utils
	{
		template<>
		class DescriptorSchema<Behavior::SimpleRotationComponentDesc> : public BaseDescriptorSchema<Behavior::SimpleRotationComponentDesc>
		{
			DescriptorSchema()
			{
				typedef Behavior::SimpleRotationComponentDesc DescriptorType;
				
				addField<Math::Transform>("initial_transform", [](DescriptorType& c, const Math::Transform& value){c.initial_transform = value;}, true);
				addField<Core::IComponent*>("update_frame_provider", [](DescriptorType& c, Core::IComponent* const & value){c.update_frame_provider = value;}, true);
				
			}
		};
	}
}