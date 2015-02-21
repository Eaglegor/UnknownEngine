#include <stdafx.h>

#include <Parsers/Descriptors/OgreSubsystemDescParser.h>
#include <Parsers/Descriptors/OgreRenderWindowDescriptorParser.h>
#include <Descriptors/OgreRenderWindowDescriptor.h>

#include <CommonParsers/LexicalCastForBoolAlpha.h>
#include <CommonParsers/PropertiesParser.h>
#include <ComponentSystem/ComponentsManager.h>

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
					{
						"ConfigFiles",
						PropertiesParser::OptionalNestedValue
						(
						{
							{"ogre_config_filename", PropertiesParser::OptionalValue<std::string>(desc.ogre_config_filename)},
							{"ogre_plugins_filename", PropertiesParser::OptionalValue<std::string>(desc.ogre_plugins_filename)},
							{"ogre_log_filename", PropertiesParser::OptionalValue<std::string>(desc.ogre_log_filename)},
							{"ogre_resources_filename", PropertiesParser::OptionalValue< std::string >( [&](const std::string& value){ desc.ogre_resources_filename = value; } )},
						}
						)
					},
					{
						"RenderWindow",
						PropertiesParser::ExternalParserOptionalNestedValue<OgreRenderWindowDescriptor, OgreRenderWindowDescriptorParser>
						(desc.render_window_descriptor)
					},
					{"separate_rendering_thread", PropertiesParser::OptionalValue<bool>(desc.separate_rendering_thread) },
					{"show_config_dialog", PropertiesParser::OptionalValue<bool>(desc.show_config_dialog) },
					{"update_frame_provider_name", PropertiesParser::OptionalValue<std::string>([&desc](const std::string& value){
						desc.update_frame_provider = Core::ComponentsManager::getSingleton()->findComponent(value.c_str());
					}
					)}
					
				}
			);
			
			return desc;
		}

	} // namespace Graphics
} // namespace UnknownEngine
