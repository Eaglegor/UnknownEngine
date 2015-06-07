#pragma once
#include <Descriptors/DescriptorUtils.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		struct OgreScreenSpaceAxisAlignedBoundingBoxCalculatorDesc : public Utils::Descriptor
		{
			Utils::RequiredComponentDependency screen_space_coordinates_calculator;
			
			OgreScreenSpaceAxisAlignedBoundingBoxCalculatorDesc()
			{
				UEDESC_ADD_FIELD(screen_space_coordinates_calculator);
			}
		};
	}
}