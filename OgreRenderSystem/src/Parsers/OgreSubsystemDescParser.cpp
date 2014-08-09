#include <stdafx.h>

#include "include/Parsers/OgreSubsystemDescParser.h"

#include <CommonParsers/LexicalCastForBoolAlpha.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		typedef boost::optional<const Core::Properties&> OptionalOptionsSection;
		typedef boost::optional<const std::string&> OptionalStringOption;


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
		
		namespace GLOBAL_OPTIONS
		{
			const std::string SHOW_CONFIG_DIALOG = "show_config_dialog";
		}

		OgreRenderSubsystem::Descriptor OgreRenderSubsystemDescriptorParser::parse ( const Core::Properties &properties )
		{
			OgreRenderSubsystem::Descriptor desc;
			
			OptionalOptionsSection render_window_section = properties.get_optional<Core::Properties>( RENDER_WINDOW_SECTION::SECTION_NAME );
			if ( render_window_section.is_initialized() )
			{
				desc.render_window_name = render_window_section->get<std::string>( RENDER_WINDOW_SECTION::OPTIONS::RENDER_WINDOW_NAME, desc.render_window_name );
			}

			OptionalOptionsSection ogre_config_files_section = properties.get_optional<Core::Properties>( CONFIG_FILES_SECTION::SECTION_NAME );
			if ( ogre_config_files_section.is_initialized() )
			{
				desc.ogre_config_filename = ogre_config_files_section->get<std::string>( CONFIG_FILES_SECTION::OPTIONS::OGRE_CONFIG_FILENAME, desc.ogre_config_filename );
				desc.ogre_plugins_filename = ogre_config_files_section->get<std::string>( CONFIG_FILES_SECTION::OPTIONS::OGRE_PLUGINS_FILENAME, desc.ogre_plugins_filename );
				desc.ogre_log_filename = ogre_config_files_section->get<std::string>( CONFIG_FILES_SECTION::OPTIONS::OGRE_LOG_FILENAME, desc.ogre_log_filename );
			}
			
			OptionalStringOption show_config_dialog = properties.get_optional<std::string>( GLOBAL_OPTIONS::SHOW_CONFIG_DIALOG );
			if(show_config_dialog.is_initialized()) desc.show_config_dialog = boost::lexical_cast<bool>(show_config_dialog.get());

			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
