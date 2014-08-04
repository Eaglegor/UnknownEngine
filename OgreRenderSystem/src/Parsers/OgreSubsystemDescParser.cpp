#include "include/Parsers/OgreSubsystemDescParser.h"

namespace UnknownEngine {
	namespace Graphics {

		OgreRenderSubsystem::Descriptor OgreRenderSubsystemDescriptorParser::parse(const Core::Properties &properties)
		{
			OgreRenderSubsystem::Descriptor desc;
			desc.render_window_name = properties.get<std::string>("render_window_name", "Unnamed window");
			desc.ogre_config_filename = properties.get<std::string>("ogre_config_filename", "ogre.cfg");
			desc.ogre_plugins_filename = properties.get<std::string>("ogre_plugins_filename", "plugins.cfg");
			desc.ogre_log_filename = properties.get<std::string>("ogre_log_filename", "Ogre.log");
			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
