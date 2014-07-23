#pragma once

#include <OgreRenderSubsystem.h>

namespace UnknownEngine {
	namespace Graphics {

		class OgreRenderSubsystemDescriptorParser
		{
			public:
				static OgreRenderSubsystem::Descriptor parse(const Core::Properties& properties);
		};

	} // namespace Graphics
} // namespace UnknownEngine
