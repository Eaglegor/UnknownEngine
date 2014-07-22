#include <stdafx.h>

#include <Parsers\OgreRenderableDescriptorParser.h>

namespace UnknownEngine {
	namespace Graphics {

		OgreRenderableDescriptorParser::OgreRenderableDescriptorParser()
		{
		}

		OgreRenderableComponent::Descriptor OgreRenderableDescriptorParser::parse(const Core::Properties &properties)
		{
			return OgreRenderableComponent::Descriptor();
		}

	} // namespace Graphics
} // namespace UnknownEngine
