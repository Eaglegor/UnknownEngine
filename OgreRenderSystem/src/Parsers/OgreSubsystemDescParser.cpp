#include "include/Parsers/OgreSubsystemDescParser.h"

namespace UnknownEngine
{
	namespace Graphics
	{

		typedef boost::optional<const Core::Properties&> OptionalOptionsSection;
#define GET_OPTIONAL_OPTIONS_SECTION(section_name) properties.get_optional<Core::Properties>(section_name);
#define OVERRIDE_DEFAULT_VALUE(config_section, option_name, output_field) output_field = config_section->get<std::string>(option_name, output_field);


		namespace RENDER_WINDOW_SECTION
		{
			const std::string SECTION_NAME = "RenderWindow"; // optional

			namespace OPTIONS
			{
				const std::string RENDER_WINDOW_NAME = "title"; // optional
			}
		}

		namespace CONFIG_FILES_SECTION
		{
			const std::string SECTION_NAME = "ConfigFiles"; // optional

			namespace OPTIONS
			{
				const std::string OGRE_CONFIG_FILENAME = "ogre_config_filename"; // optional
				const std::string OGRE_PLUGINS_FILENAME = "ogre_plugins_filename"; // optional
				const std::string OGRE_LOG_FILENAME = "ogre_log_filename"; // optional
			}
		}

		OgreRenderSubsystem::Descriptor OgreRenderSubsystemDescriptorParser::parse ( const Core::Properties &properties )
		{
			OgreRenderSubsystem::Descriptor desc;
			
			OptionalOptionsSection render_window_section = GET_OPTIONAL_OPTIONS_SECTION ( RENDER_WINDOW_SECTION::SECTION_NAME );
			if ( render_window_section.is_initialized() )
			{
				OVERRIDE_DEFAULT_VALUE ( render_window_section, RENDER_WINDOW_SECTION::OPTIONS::RENDER_WINDOW_NAME, desc.render_window_name );
			}

			OptionalOptionsSection ogre_config_files_section = GET_OPTIONAL_OPTIONS_SECTION ( CONFIG_FILES_SECTION::SECTION_NAME );
			if ( ogre_config_files_section.is_initialized() )
			{
				OVERRIDE_DEFAULT_VALUE ( ogre_config_files_section, CONFIG_FILES_SECTION::OPTIONS::OGRE_CONFIG_FILENAME, desc.ogre_config_filename );
				OVERRIDE_DEFAULT_VALUE ( ogre_config_files_section, CONFIG_FILES_SECTION::OPTIONS::OGRE_PLUGINS_FILENAME, desc.ogre_plugins_filename );
				OVERRIDE_DEFAULT_VALUE ( ogre_config_files_section, CONFIG_FILES_SECTION::OPTIONS::OGRE_LOG_FILENAME, desc.ogre_log_filename );
			}

			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
