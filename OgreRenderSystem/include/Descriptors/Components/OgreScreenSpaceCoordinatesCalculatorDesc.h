#pragma once

#include <Transform/Transform.h>
#include <AlignedNew.h>
#include <boost/optional.hpp>
#include <LogSeverity.h>
#include <Descriptors/DescriptorUtils.h>
#include <Descriptors/CommonDescriptors/TransformDescriptor.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		struct OgreScreenSpaceCoordinatesCalculatorDesc : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;

			Utils::RequiredComponentDependency camera;
			
			OgreCameraComponentDescriptor()
			{
				UEDESC_ADD_FIELD(camera);
			}
		};
	}
}

