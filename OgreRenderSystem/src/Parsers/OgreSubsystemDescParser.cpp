#include "include/Parsers/OgreSubsystemDescParser.h"

namespace UnknownEngine {
	namespace Graphics {

		OgreRenderSubsystem::Descriptor OgreRenderSubsystemDescriptorParser::parse(const Core::Properties &properties)
		{
			OgreRenderSubsystem::Descriptor desc;
			desc.render_window_name = properties.get<std::string>("render_window_name", "Unnamed window");
			desc.config_filename = properties.get<std::string>("config_filename", "");
		}

	} // namespace Graphics
} // namespace UnknownEngine
