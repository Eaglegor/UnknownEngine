#include <stdafx.h>

#include <Parsers/Descriptors/OgreSubsystemDescParser.h>
#include <Parsers/Descriptors/OgreRenderWindowDescriptorParser.h>
#include <Descriptors/OgreRenderWindowDescriptor.h>

#include <CommonParsers/LexicalCastForBoolAlpha.h>
#include <CommonParsers/PropertiesParser.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderSubsystemDescriptor OgreRenderSubsystemDescriptorParser::parse ( const Core::Properties &properties )
		{
			OgreRenderSubsystemDescriptor desc;
		
			using Utils::PropertiesParser;
			
			PropertiesParser::parse
			(
				properties,
				{
					{"render_window_name", PropertiesParser::OptionalValue<std::string>(desc.render_window_name)},
					{
						"ConfigFiles",
						PropertiesParser::OptionalNestedValue
						(
						{
							{"ogre_config_filename", PropertiesParser::OptionalValue<std::string>(desc.ogre_config_filename)},
							{"ogre_plugins_filename", PropertiesParser::OptionalValue<std::string>(desc.ogre_plugins_filename)},
							{"ogre_log_filename", PropertiesParser::OptionalValue<std::string>(desc.ogre_log_filename)},
							{"ogre_resources_filename", PropertiesParser::OptionalValue< std::string >(desc.ogre_resources_filename)}
						}
						)
					},
					{"separate_rendeing_thread", PropertiesParser::OptionalValue<bool>(desc.separate_rendering_thread) },
					{"show_config_dialog", PropertiesParser::OptionalValue<bool>(desc.show_config_dialog) }
					
				}
			);
			
			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
